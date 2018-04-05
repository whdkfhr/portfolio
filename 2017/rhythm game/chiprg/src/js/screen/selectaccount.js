var screenSelectAccount = {
  name: "screenSelectAccount",
  uiPath: "",

  // Strings
  string: {
    title: "SELECT ACCOUNT TYPE",
    type1: {
      name: "ONLINE ACCOUNT",
      contents: "ONLINE RANKING AVAILABLE\nSAVE DATA ON ONLINE\n"
    },
    type2: {
      name: "LOCAL ACCOUNT",
      contents: "LOCAL RANKING AVAILABLE\nSAVE DATA ON LOCAL\n"
    },
    type3: {
      name: "GUEST ACCOUNT",
      contents: "LOCAL RANKING AVAILABLE\nNO SAVE DATA\n"
    },
  },

  // Image Objects
  img: {
    background: "",
    selector: "",
    type1button: "",
    type2button: "",
    type3button: "",
    okbutton: "",
  },

  // Text Objects
  text: {
    title: "",
    buttontype1: "",
    buttontype2: "",
    buttontype3: "",
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
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmSelectAccount.mod');
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
      10, 80, 'button', this.type2touched, this);
    this.img.type3button = game.add.button(
      10, 130, 'button', this.type3touched, this);

    this.text.buttontype1 = game.add.bitmapText(40, 45, 'font79', this.string.type1.name, 9);
    this.text.buttontype2 = game.add.bitmapText(40, 95, 'font79', this.string.type2.name, 9);
    this.text.buttontype3 = game.add.bitmapText(40, 145, 'font79', this.string.type3.name, 9);
    this.text.typename = game.add.bitmapText(190, 20, 'font79', this.string.type1.name, 9);
    this.text.okname = game.add.bitmapText(210, 147, 'font57', 'USE '+this.string.type1.name, 7);
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
    if (isOver) this.pressokbutton();
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

  moveSelector: function(selection) {
    switch(selection){
      case 0:
      case 1:
      case 2:
        this.var.selectType = selection;
        break;
      default:
        if(selection == 'down'){
          if(this.var.selectType >= 2)
            this.var.selectType = 0;
          else
            this.var.selectType++;
        }
        else if(selection == 'up'){
          if(this.var.selectType <= 0)
            this.var.selectType = 2;
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
        this.img.selector.y=80;
        this.text.typename.setText(this.string.type2.name);
        this.text.okname.setText('USE '+this.string.type2.name);
        this.text.contents.setText(this.string.type2.contents);
        break;
      case 2:
        this.img.selector.y=130;
        this.text.typename.setText(this.string.type3.name);
        this.text.okname.setText('USE '+this.string.type3.name);
        this.text.contents.setText(this.string.type3.contents);
        break;
      default:
    }
  },

  pressokbutton: function() {
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    switch(this.var.selectType){
      case 0:
        console.log('go online account');
        game.state.start('screenLogin');
        break;
      case 1:
        console.log('go local account');
        game.state.start('screenLobby');
        break;
      case 2:
        console.log('go guest account');
        currentUser.load({type: "guest"});
        game.state.start('screenLobby');
        break;
      default:
    }
  }
};
