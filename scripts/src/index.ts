/* eslint-disable no-console */
import { exec } from "child_process";
import { exists, stat, readdir, mkdtemp, copyFile } from "fs/promises";
import { tmpdir } from "os";
import { join } from "path";
import {
  intro,
  select,
  multiselect,
  spinner,
  confirm,
  cancel,
  text,
  outro,
  isCancel,
} from "@clack/prompts";
import AdmZip from "adm-zip";
import packageJson from "packageJson";
import pc from "picocolors";
import { match } from "ts-pattern";

type Kind = "practice" | "issues";
interface FileOption {
  value: string;
  label: string;
}
type ExcludeSymbol<T> = T extends symbol ? never : T;

const waitMs = async (ms: number): Promise<void> => {
  await new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
};

function checkCancel<T>(data: T): ExcludeSymbol<T> | never {
  if (isCancel(data)) {
    cancel("キャンセルしました");
    process.exit(1);
  }
  return (data ?? "") as ExcludeSymbol<T>;
}

const getStudentId = async (): Promise<string> => {
  const id = await text({
    message: "まず, 学籍番号を教えてください.",
    placeholder: "k2xxxx",
    validate: (value) => {
      if (!value.match(/^k2\d{4}$/)) {
        return "学籍番号の形式が違います";
      }
      return undefined;
    },
  });

  return checkCancel(id);
};

const getSubmissionType = async (): Promise<Kind> => {
  const type = (await select({
    message: "これはどんな提出物ですか？",
    options: [
      {
        value: "practice",
        label: "演習問題",
        hint: "講義の中で行った問題のことだよ.",
      },
      {
        value: "issues",
        label: "課題, チャレンジ問題",
        hint: "問題詳細の最後のほうにある問題だよ.",
      },
    ],
  })) as Kind;

  return checkCancel(type);
};

const getSourceDirectory = async (): Promise<string> => {
  const directory = await text({
    message:
      "ソースコードを含んだディレクトリを指定してください (Finder から D&D しても OK)",
    placeholder: "~/src/prg1k/src/05",
  });
  return checkCancel(directory)
    .replace(/^['"]|['"]$/g, "")
    .replace(/\s+$/, "");
};

const validateSourceDirectory = async (src: string): Promise<void> => {
  if (!(await exists(src))) {
    checkCancel("指定されたディレクトリが存在しません！");
    process.exit(1);
  }
  if (!(await stat(src)).isDirectory()) {
    checkCancel("指定されたパスはディレクトリではありません！");
    process.exit(1);
  }
};

const readDirectory = async (src: string): Promise<string[]> => {
  const spinnerDir = spinner();
  spinnerDir.start("ディレクトリを読み取り中...");
  const files = (await readdir(src)).sort();
  spinnerDir.stop("ディレクトリを読み取りました！");
  return files;
};

const selectFiles = async (options: FileOption[]): Promise<string[]> => {
  const selectedFiles = (await multiselect({
    message:
      "ZIP にしたいファイルを選択してください (移動: ↑↓, 選択: Space, 確定: Enter, 全選択: a)",
    options,
  })) as string[];
  return checkCancel(selectedFiles);
};

const getPrefix = async (init: string | undefined): Promise<string> => {
  const prefix =
    (await text({
      message: "ファイル名の最初につける文字を入力してください",
      placeholder: `(講義回: \`05_\` など.  \`Enter\` で${
        init != null ? ` \`${init}\` (親ディレクトリー名)` : "何もつけない"
      })`,
      initialValue: "",
      validate: (value) => {
        if (value.match(/[\\/:*?"<>|]/) != null) {
          return "ファイル名に使える文字で入力してください";
        }
        return undefined;
      },
    })) ?? init;
  return checkCancel(prefix);
};

const getSuffix = async (kind: Kind, name: string): Promise<string> => {
  const init = kind === "issues" ? `_${name}` : "";
  const suffix =
    (await text({
      message: "ファイル名の最後につける文字を入力してください",
      placeholder:
        kind === "issues"
          ? `(Enter で _<学籍番号: \`${init}\`> を入力)`
          : "(Enter で何もつけない)",
      initialValue: "",
      validate: (value) => {
        if (value.match(/[\\/:*?"<>|]/) != null) {
          return "ファイル名に使える文字で入力してください";
        }
        return undefined;
      },
    })) ?? init;
  return checkCancel(suffix);
};

const renameFiles = (
  filePathList: string[],
  prefix: string,
  suffix: string,
): string[] =>
  filePathList.map((f) => {
    const ext = f.split(".").at(-1);
    if (ext != null) {
      const fileNameWithoutExt = f.replace(/\.[^/.]+$/, "");
      return `${prefix}${fileNameWithoutExt}${suffix}.${ext}`;
    }
    return `${prefix}${f}${suffix}`;
  });

const highlightFileNames = (
  filePathList: string[],
  prefix: string,
  suffix: string,
): string[] =>
  filePathList.map((f) => {
    const ext = f.split(".").at(-1);
    if (ext != null) {
      const fileNameWithoutExt = f.replace(/\.[^/.]+$/, "");
      return `${pc.red(prefix)}${fileNameWithoutExt}${pc.red(suffix)}.${ext}`;
    }
    return `${pc.red(prefix)}${f}${pc.red(suffix)}`;
  });

const confirmZipCreation = async (
  highlightedFiles: string[],
): Promise<void> => {
  const _confirm = await confirm({
    message: `次のファイル名で ZIP を作成しますか？\n - ${highlightedFiles.join(
      "\n  - ",
    )} `,
  });
  checkCancel(_confirm);
  if (!_confirm) {
    cancel("キャンセルしました");
    process.exit(1);
  }
};

const copyFiles = async (
  filePathList: string[],
  src: string,
  workDir: string,
  namedFiles: string[],
): Promise<void> => {
  const spinnerCopy = spinner();
  spinnerCopy.start("ファイルをコピー中...");

  filePathList.forEach(async (f, i) => {
    const from = `${src}/${f}`;
    const to = `${workDir}/${namedFiles[i]}`;
    await copyFile(from, to);
    await waitMs(100);
    spinnerCopy.message(`[${i + 1}/${filePathList.length}]: ${from} -> ${to}`);
  });

  spinnerCopy.stop(`${filePathList.length} ファイルをコピーしました！`);
};

const createZip = async (
  workDir: string,
  kind: Kind,
  name: string,
): Promise<string> => {
  const zipNameEntries = {
    practice: name,
    issues: `${name}_issues`,
  } as const satisfies Record<Kind, string>;

  const zipDir = await mkdtemp(join(tmpdir(), "prg1k-"));
  const zipName = `${zipNameEntries[kind]}.zip`;
  const zipPath = join(zipDir, zipName);

  const spinnerZip = spinner();
  spinnerZip.start("ZIP を作成中...");
  const zip = new AdmZip();
  await zip.addLocalFolderPromise(workDir, {});
  await zip.writeZipPromise(zipPath);
  spinnerZip.stop(`ファイル名 \`${zipName}\` で ZIP を作成しました！`);

  return zipPath;
};

const openPath = async (path: string): Promise<void> => {
  const command = match(process.platform)
    .with("win32", () => "explorer")
    .with("darwin", () => "open")
    .otherwise(() => "xdg-open");
  exec(`${command} ${path}`);
};

const main = async (): Promise<void> => {
  intro(
    `Cook Zip v${packageJson.version} — プログラミング実習の提出物を ZIP にするよ`,
  );

  const name = await getStudentId();
  const kind = await getSubmissionType();
  const src = await getSourceDirectory();
  await validateSourceDirectory(src);

  const files = await readDirectory(src);
  const options = files.map((f) => ({ value: f, label: f }));
  const filePathList = await selectFiles(options);

  const _parentDir = match(src.split("/").at(-1))
    .when(
      (s) => s?.match(/^\d{2}$/) != null,
      (s) => `${s}_`,
    )
    .otherwise(() => undefined);

  const prefix = await getPrefix(_parentDir);
  const suffix = await getSuffix(kind, name);
  const namedFiles = renameFiles(filePathList, prefix, suffix);
  const highlightedFiles = highlightFileNames(filePathList, prefix, suffix);

  await confirmZipCreation(highlightedFiles);

  const workDir = await mkdtemp(join(tmpdir(), "prg1k-"));
  await copyFiles(filePathList, src, workDir, namedFiles);

  const zipPath = await createZip(workDir, kind, name);

  outro("さようなら！");
  await waitMs(1000);

  await openPath(zipPath);
};

main().catch((err) => {
  cancel("エラーが発生しました");
  console.error(err);
  process.exit(1);
});
