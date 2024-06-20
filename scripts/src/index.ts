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

const REPOSITORY_URL = "https://github.com/wappon28dev/prg1k/releases/latest";
const FORMULA_URL = "wappon28dev/tap/cook-zip";

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

async function checkUpdate(): Promise<void> {
  const spinnerDir = spinner();
  spinnerDir.start("アップデートを確認中...");
  const res = await fetch(REPOSITORY_URL, { redirect: "follow" });

  if (!res.ok) {
    spinnerDir.stop(
      pc.red(`アップデートを確認できませんでした: ${res.statusText}`),
    );
    return;
  }

  const url = new URL(res.url);
  const latestVersion = url.pathname.split("/").at(-1)?.replace("v", "");

  if (latestVersion !== packageJson.version) {
    spinnerDir.stop(
      `
   新しいバージョンが見つかりました！ v${
     packageJson.version
   } -> v${latestVersion}
   更新するには以下のコマンドを実行してください:
   ${pc.yellow(`brew upgrade ${FORMULA_URL}`)}

   または, 以下の URL から最新バージョンをダウンロードできます:
   ${pc.yellow(REPOSITORY_URL)}

   ${pc.gray("終了します...")}
      `.trim(),
    );

    throw new Error("Found new version.");
  }

  spinnerDir.stop(pc.green("最新バージョンです！ やったー！"));
}

function checkCancel<T>(data: T): ExcludeSymbol<T> | never {
  if (isCancel(data)) {
    cancel("キャンセルしました");
    process.exit(1);
  }
  return (data ?? "") as ExcludeSymbol<T>;
}

const getStudentId = async (): Promise<string> => {
  const id = await text({
    message: "学籍番号は入力してください",
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
    placeholder: "~/src/prg1k/src/05 など",
    validate: (value) => {
      if (value === "") {
        return "ディレクトリを指定してください";
      }
      return undefined;
    },
  });
  return checkCancel(directory)
    .replace(/^['"]|['"]$/g, "")
    .replace(/\s+$/, "");
};

const validateSourceDirectory = async (src: string): Promise<void> => {
  if (!(await exists(src))) {
    cancel("指定されたディレクトリが存在しません！");
    process.exit(1);
  }
  if (!(await stat(src)).isDirectory()) {
    cancel("指定されたパスはディレクトリではありません！");
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
      placeholder: `講義回: \`05_\` など.  Enter キーで ${
        init != null
          ? `\`${pc.yellow(init)}\` (親ディレクトリー名)`
          : `${pc.yellow("<何も付けない>")}`
      }`,
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

const getSuffix = async (init: string | undefined): Promise<string> => {
  const suffix =
    (await text({
      message: "ファイル名の最後につける文字を入力してください",
      placeholder: `Enter キーで ${
        init != null ? pc.yellow(init) : pc.yellow("<何も付けない>")
      }`,
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

const confirmNonZipCreation = async (
  highlightedFiles: string[],
): Promise<void> => {
  const _confirm = await confirm({
    message: `おっと！  ファイルを圧縮する必要は無さそうです.  次のファイル名でファイルをコピーしますか？\n - ${highlightedFiles.join(
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

const byebye = async (path: string): Promise<void> => {
  outro("さようなら！");
  await waitMs(1000);
  await openPath(path);
};

const main = async (): Promise<void> => {
  intro(
    `${pc.yellow(
      `Cook Zip v${packageJson.version}`,
    )} — プログラミング実習の提出物を ZIP にするよ`,
  );

  await checkUpdate();

  const name = await getStudentId();
  const kind = await getSubmissionType();
  const src = await getSourceDirectory();
  await validateSourceDirectory(src);

  const files = await readDirectory(src);
  const options = files.map((f) => ({ value: f, label: f }));
  const filePathList = await selectFiles(options);

  const _prefix = match(src.split("/").at(-1))
    .when(
      () => filePathList.every((f) => f.match(/^\d{2}_\d{2}_/) != null),
      () => undefined,
    )
    .when(
      (s) => s?.match(/^\d{2}$/) != null,
      (s) => `${s}_`,
    )
    .otherwise(() => undefined);

  const _suffix = match(filePathList)
    .when(
      () => kind !== "issues",
      () => undefined,
    )
    .when(
      (fs) => fs.every((f) => f.match(/_k\d{5}.c$/) != null),
      () => undefined,
    )
    .otherwise(() => `_${name}`);

  const prefix = await getPrefix(_prefix);
  const suffix = await getSuffix(_suffix);
  const namedFiles = renameFiles(filePathList, prefix, suffix);
  const highlightedFiles = highlightFileNames(filePathList, prefix, suffix);
  const workDir = await mkdtemp(join(tmpdir(), "prg1k-"));

  if (namedFiles.length > 0) {
    await confirmNonZipCreation(highlightedFiles);

    await copyFiles(filePathList, src, workDir, namedFiles);

    await byebye(workDir);
  } else {
    await confirmZipCreation(highlightedFiles);

    await copyFiles(filePathList, src, workDir, namedFiles);
    const zipPath = await createZip(workDir, kind, name);

    await byebye(zipPath);
  }
};

main().catch((err) => {
  cancel("エラーが発生しました");
  console.error(err);
  process.exit(1);
});
