import { ESLint } from "eslint";
import micromatch from "micromatch";

const removeIgnoredFiles = async (files) => {
  const eslint = new ESLint();
  const isIgnored = await Promise.all(
    files.map((file) => {
      return eslint.isPathIgnored(file);
    })
  );
  const filteredFiles = files.filter((_, i) => !isIgnored[i]);
  return filteredFiles.join(" ");
};

export default {
  "**/!(package-lock)*": async (files) => {
    const filesToLint = await removeIgnoredFiles(micromatch(files, ["**/!(__)*.{ts,js}"]));
    return [
      `eslint --fix --max-warnings=0 ${filesToLint}`,
      `prettier --write --ignore-unknown ${files.join(" ")}`
    ];
  }
};
