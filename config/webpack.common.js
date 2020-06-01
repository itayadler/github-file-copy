const path = require("path");
const CopyWebpackPlugin = require("copy-webpack-plugin");

const distDir = path.join(__dirname, "..", "dist");

module.exports = {
  entry: {
    background: "./src/Background.bs.js",
    contentscript: "./src/ContentScript.bs.js",
  },
  node: {
    fs: "empty",
  },
  output: {
    filename: "[name].js",
    path: distDir,
    publicPath: "/",
  },
  plugins: [
    new CopyWebpackPlugin(
      [
        {
          from: "./manifest.json",
          to: "./",
          flatten: true,
          transform: function (content, path) {
            // generates the manifest file using the package.json informations
            let manifestContent = JSON.parse(content.toString());
            if (process.env.NODE_ENV !== "development") {
              delete manifestContent.key;
            }
            return Buffer.from(
              JSON.stringify({
                description: process.env.npm_package_description,
                version: process.env.npm_package_version,
                name: process.env.npm_package_name,
                ...manifestContent,
              })
            );
          },
        },
        {
          from: "./icons/*",
          to: "./icons",
          flatten: true,
        },
      ],
      {
        copyUnmodified: true,
      }
    ),
  ],
  node: {
    module: "empty",
    dgram: "empty",
    dns: "mock",
    fs: "empty",
    http2: "empty",
    net: "empty",
    tls: "empty",
    child_process: "empty",
  },
};
