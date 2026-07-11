## Libbchat-util NodeJS

This library is the wrappers around libbchat-uti for NodeJS. It is built using the [node-addon-api](https://github.com/nodejs/node-addon-api) and [cmake-js](https://github.com/cmake-js/cmake-js). The build and dev instructions are quite custom, so check them out below.

### Dev instructions

Clone this project to somewhere **not** part of `bchat-desktop` node_modules:

```
cd [FOLDER_NOT_IN_BCHAT_DESKTOP]
git clone --recursive git@github.com:peter-pratt/libbchat-util-nodejs.git
```

Always do your changes in `[FOLDER_NOT_IN_BCHAT_DESKTOP]/libbchat-uti-nodejs`, never in the one under bchat-desktop's `node_modules` as you might override your local changes.
Then, you can quickly compile a non-electron build by first running `pnpm install` from that folder. This is a quick incremental build which can check for C++ compilation errors.
Once your changes are ready to be tested in the `bchat-desktop` you can compile an electron build using this command:

```
cd [bchat_DESKTOP_PATH]; rm -rf node_modules/libbchat_util_nodejs; cp -R [THIS_PROJECT_PATH] node_modules/libbchat_util_nodejs; cd node_modules/libbchat_util_nodejs && rm -rf build && pnpm install && cd [BCHAT_DESKTOP_PATH] && pnpm build:workers
```

Replace `[BCHAT_DESKTOP_PATH]` with the full path to your `bchat-desktop` folder, replace `[THIS_PROJECT_PATH]` with the path to the root of this project folder.

Every part of this command is needed and might need to be updated using your paths. Also, the `worker:libbchat` needs to be recompiled too to include the just created .node file in itself. This is done by the `pnpm build:workers` command.

Note: The `electron` property in the `config` object will need to be updated in the `package.json` every time we update `electron` package in [bchat-desktop](https://github.com/Beldex-Coin/bchat-desktop/) so that the versions match. It is a node version, but not part of the official node docs. If you compiled the node module for an incorrect electron/node version you will get an error on `bchat-desktop` start.

### Making a Release and updating Bchat-desktop

1. First, make sure all your changes are committed and pushed to the `libbchat-uti-nodejs` project from your `[FOLDER_NOT_IN_BCHAT_DESKTOP]` folder.

2. Then make sure the `libbchat-uti` is using the latest `dev` branch (unless there is a reason not to).

3. Then, bump the version in the package.json of the nodejs wrapper.

   - A **patch** version bump is required only if you have changed the implementation of an existing function or doing a hot fix for libbchat version used by `bchat-desktop`.

   - A **minor** version bump is required if you have added a new function or changed the signature of an existing one.

Then, run these commands:

```
# bump the version in the package.json
git add .
git commit
git push upstream main
# Make sure you do the steps above, otherwise the tag won't be on the right commit with the `gh release create`

pnpm prepare_release
```

And then upload the generated `libbchat_util_nodejs-v$PACKAGE_VERSION.tar.gz` to that release just created on github.
The git-archive-all relies on the `.gitattributes` to know what to include or exclude.

Once this is done, update the dependency on `bchat-desktop`.
Make sure to remove the existing one first (with the include `pnpm remove` below) as you might have messed up your `node_modules` doing the dev instructions.

```
pnpm remove libbchat_util_nodejs && pnpm add https://github.com/peter-pratt/libbchat-uti-nodejs/releases/download/v0.1.15/libbchat_util_nodejs-v0.1.15.tar.gz
```

Keep in mind that you need to update the two version numbers (e.g. `0.1.15`) to the just created release version of this project.

The cmake-js script will be run on the pnpm add and should recompile your latest release of the `libbchat-uti-nodejs` as part of the build process and as part of the github actions on `bchat-desktop`.
You most likely need to recompile the workers to include those new changes: `pnpm worker:utils && pnpm worker:libbchat`.

You should have your changes in the next release!
