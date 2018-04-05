# chiprg

# Run on Browser

require `nodejs` & `npm`

install http-server at global (just for once)
```bash
$ npm install -g http-server
```

run http-server
```bash
$ http-server src/
```

open `localhost:8080/` on your browser

# Run on cordova

install cordova at global (just for once)
```bash
$ npm install -g cordova
```

create cordova project on `~/workspace/`
```
$ cordova create ~/workspace/chiprg_cordova #or your workspace instead ~/workspace/
```

copy `src/` to cordova project and rename
```
$ cp -r src/ ~/workspace/chiprg_cordova/
$ rm -rf ~/workspace/chiprg_cordova/www/
$ mv ~/workspace/chiprg_cordova/src/ ~/workspace/chiprg_cordova/www/
```

copy `config.xml` to cordova project
```
$ cp cordova_app/config.xml ~/workspace/chiprg_cordova/
```

build and run cordova project
```
$ cd ~/workspace/chiprg_cordova/
$ cordova platform add android #or your platform instead android
$ cordova run android #or your platform
```

# Run on Electron

install electron at global (just for once)
```bash
$ npm install -g electron
```

copy `src/` to electron folder
```
$ cp -r src/ electron_app/
```

run electron folder
```
$ electron electron_app/
```