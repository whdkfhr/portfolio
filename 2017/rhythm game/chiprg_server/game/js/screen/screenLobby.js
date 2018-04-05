var screenLobby = {
  name: "screenLobby",
  uiPath: "",

  // Strings
  string: {
    title: "LOBBY",
    type1: {
      name: "FREE PLAY",
      contents: "JUST PLAY ONE SONG"
    },
    type2: {
      name: "COURSE PLAY",
      contents: "PLAY COURSE WITH\nCOLLECTION OF 4 SONGS"
    },
    type3: {
      name: "PLAYER INFO",
      contents: "READ PLAYER INFORMATION"
    },
    type4: {
      name: "RANKING INFO",
      contents: "READ RANKING INFORMATION"
    },
    type5: {
      name: "CONFIG",
      contents: "SET CONFIGURATION"
    },
    type6: {
      name: "LOGOUT",
      contents: "SELECT ANOTHER ACCOUNT"
    },
  },

  // Image Objects
  img: {
    background: "",
    selector: "",
    type1button: "",
    type2button: "",
    type3button: "",
    type4button: "",
    type5button: "",
    type6button: "",
    okbutton: "",
  },

  // Text Objects
  text: {
    title: "",
    buttontype1: "",
    buttontype2: "",
    buttontype3: "",
    buttontype4: "",
    buttontype5: "",
    buttontype6: "",
    typename: "",
    okname: "",
    contents: "",
  },

  // Variable
  var:{
    selectType: 0, // 0: Online, 1: Local, 2: Guest
  },

  preload: function(){
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
    game.load.image('background', this.uiPath+'background.png');
    game.load.image('selector', this.uiPath+'selector.png');
    game.load.image('button', this.uiPath+'button.png');
    game.load.spritesheet('ok', this.uiPath+'ok.png',110,23);
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmStart.mod');
  },
  create: function(){
    C2TrackerControl.play(C2Trackers.bgmLoop);
    this.text.title = game.add.bitmapText(0, 0, 'font79', this.string.title, 9);
    this.img.background = game.add.sprite(0, 0, 'background');
    this.img.selector = game.add.sprite(160, 30, 'selector');

    this.img.okbutton = game.add.button(
      190, 140, 'ok', this.oktouched, this, 1, 1, 2);
    this.img.type1button = game.add.button(
      10, 30, 'button', this.type1touched, this);
    this.img.type2button = game.add.button(
      10, 54, 'button', this.type2touched, this);
    this.img.type3button = game.add.button(
      10, 78, 'button', this.type3touched, this);
    this.img.type4button = game.add.button(
      10, 102, 'button', this.type4touched, this);
    this.img.type5button = game.add.button(
      10, 126, 'button', this.type5touched, this);
    this.img.type6button = game.add.button(
      10, 150, 'button', this.type6touched, this);

    this.text.buttontype1 = game.add.bitmapText(40, 37, 'font57', this.string.type1.name, 7);
    this.text.buttontype2 = game.add.bitmapText(40, 61, 'font57', this.string.type2.name, 7);
    this.text.buttontype3 = game.add.bitmapText(40, 85, 'font57', this.string.type3.name, 7);
    this.text.buttontype4 = game.add.bitmapText(40, 109, 'font57', this.string.type4.name, 7);
    this.text.buttontype5 = game.add.bitmapText(40, 133, 'font57', this.string.type5.name, 7);
    this.text.buttontype6 = game.add.bitmapText(40, 157, 'font57', this.string.type6.name, 7);
    this.text.typename = game.add.bitmapText(190, 20, 'font79', this.string.type1.name, 9);
    this.text.okname = game.add.bitmapText(210, 147, 'font57', this.string.type1.name, 7);
    this.text.contents = game.add.bitmapText(190, 40, 'font57', this.string.type1.contents, 7);

  },

  update: function(){
    if (game.input.keyboard.justPressed(Phaser.Keyboard.UP) ||
        game.input.gamepad.pad1.justPressed(Phaser.Gamepad.XBOX360_DPAD_UP))
      this.moveSelector('up');
    if (game.input.keyboard.justPressed(Phaser.Keyboard.DOWN) ||
        game.input.gamepad.pad1.justPressed(Phaser.Gamepad.XBOX360_DPAD_DOWN))
      this.moveSelector('down');
    if (game.input.keyboard.justPressed(Phaser.Keyboard.ENTER) ||
        game.input.gamepad.pad1.justPressed(Phaser.Gamepad.XBOX360_START) ||
        game.input.gamepad.pad1.justPressed(Phaser.Gamepad.XBOX360_B))
      this.pressokbutton();
  },

  oktouched: function(okbutton, pointer, isOver){
    if (isOver){
      this.pressokbutton();
    }
  },
  type1touched: function(type1button, pointer, isOver){
    if (isOver) this.moveSelector(0);
  },
  type2touched: function(type2button, pointer, isOver){
    if (isOver) this.moveSelector(1);
  },
  type3touched: function(type3button, pointer, isOver){
    if (isOver) this.moveSelector(2);
  },
  type4touched: function(type4button, pointer, isOver){
    if (isOver) this.moveSelector(3);
  },
  type5touched: function(type5button, pointer, isOver){
    if (isOver) this.moveSelector(4);
  },
  type6touched: function(type6button, pointer, isOver){
    if (isOver) this.moveSelector(5);
  },

  moveSelector: function(selection) {
    switch(selection){
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        this.var.selectType = selection;
        break;
      default:
        if(selection == 'down'){
          if(this.var.selectType >= 5)
            this.var.selectType = 0;
          else
            this.var.selectType++;
        }
        else if(selection == 'up'){
          if(this.var.selectType <= 0)
            this.var.selectType = 5;
          else
            this.var.selectType--;
        }
        else {
        }
    }
    this.selectionUpdate();
  },

  selectionUpdate: function() {
    switch(this.var.selectType){
      case 0:
        this.img.selector.y=30;
        this.text.typename.setText(this.string.type1.name);
        this.text.okname.setText('USE '+this.string.type1.name);
        this.text.contents.setText(this.string.type1.contents);
        break;
      case 1:
        this.img.selector.y=54;
        this.text.typename.setText(this.string.type2.name);
        this.text.okname.setText('USE '+this.string.type2.name);
        this.text.contents.setText(this.string.type2.contents);
        break;
      case 2:
        this.img.selector.y=78;
        this.text.typename.setText(this.string.type3.name);
        this.text.okname.setText('USE '+this.string.type3.name);
        this.text.contents.setText(this.string.type3.contents);
        break;
      case 3:
        this.img.selector.y=102;
        this.text.typename.setText(this.string.type4.name);
        this.text.okname.setText('USE '+this.string.type4.name);
        this.text.contents.setText(this.string.type4.contents);
        break;
      case 4:
        this.img.selector.y=126;
        this.text.typename.setText(this.string.type5.name);
        this.text.okname.setText('USE '+this.string.type5.name);
        this.text.contents.setText(this.string.type5.contents);
        break;
      case 5:
        this.img.selector.y=150;
        this.text.typename.setText(this.string.type6.name);
        this.text.okname.setText('USE '+this.string.type6.name);
        this.text.contents.setText(this.string.type6.contents);
        break;
      default:
    }
  },

  pressokbutton: function() {
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    switch(this.var.selectType){
      case 0:
        console.log('go free play');
        game.state.start('screenFreePlayInit');
        break;
      case 1:
        console.log('go course play');
        game.state.start('screenCoursePlayInit');
        break;
      case 2:
        console.log('player info');
        game.state.start('');
        break;
      case 3:
        console.log('ranking info');
        game.state.start('screenRankingInit');
        break;
      case 4:
        console.log('config');
        game.state.start('');
        break;
      case 5:
        console.log('go back');
        currentUser.init();
        game.state.start('screenSelectAccount');
        break;
      default:
    }
  }

};
