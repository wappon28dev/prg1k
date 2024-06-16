const src = "";

const main = () => {
  let _parentDir: string | undefined;
  const lastDirName = src.split("/").at(-1);
  if (lastDirName.match(/^\d{2}$/) != null) {
    _parentDir = `${lastDirName}_`;
  } else {
    _parentDir = undefined;
  }

  console.log(_parentDir);
};
