var screenFreePlay = {
  name: "screenFreePlay",
  uiPath: "",

  string: {
    screenTitle: "FREE PLAY",
    optionTitle: "OPTION",
    speedTitle: "SPEED",
    skinTitle: "SKIN",
    noteTitle: "NOTE",
  },

  text: {
    screenTitle: "",
    song: [],
    optionTitle: "",
    speedTitle: "",
    skinTitle: "",
    noteTitle: "",

    speedValue: ""
  },

  img: {
    background: "",
    songselector: "",
    patternselector: "",
    songimg: "",

    optionselector: "",
    speed: "",
    skin: "",
    note: "",
  },
  button: {
    pattern0: "",
    pattern1: "",
    pattern2: "",

    song0: "",
    song1: "",
    song2: "",
    song3: "",
    song4: "",
    song5: "",

    speedL: "",
    speedR: "",
    skinL:"",
    skinR:"",
    noteL:"",
    noteR:"",

    backspace: "",
    help: "",
    start: "",
    option: "",
  },
  flag: {
    start: false,
    optionWindow: false,
  },
  var: {
    selectedSongNum: 0,
    selectedSongName: "",
    selectedPattern: 0,
    allPlaylist: "",
    currentPlaylist: {
      list: [],
      init: function(allPlaylist){
        this.update(allPlaylist, 0);
      },
      update: function(allPlaylist, selected){
        for(var i=0; i<7; i++){
          var j = SomeMath.modulo((i-3 + selected), allPlaylist.max);
          this.list[i] = allPlaylist.list[j];
        }
      }
    },
    selectedOptionNum: 0,
    selectedSpeedNum: 8,
    selectedSkinNum: 0,
    selectedNoteNum: 0,

    selectedSpeedValue: 200,
  },

  preload: function(){

    // Load Images
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
    game.load.image('background', this.uiPath+'background.png');
    game.load.image('backspacebutton', this.uiPath+'backspace.png');
    game.load.image('helpbutton', this.uiPath+'help.png');
    game.load.image('option', this.uiPath+'option.png');
    game.load.image('patternselector', this.uiPath+'patternselector.png');
    game.load.image('songselector', this.uiPath+'songselector.png');
    game.load.image('startbutton', this.uiPath+'start.png',110,23);
    game.load.image('optionWindow', this.uiPath+'optionWindow.png');
    game.load.image('invisible', this.uiPath+'invisible.png');
    game.load.image('optionselector', this.uiPath+'optionselector.png');

    for(var i=0; i<screenFreePlayInit.allPlaylist.max; i++){
      game.load.spritesheet(screenFreePlayInit.allPlaylist.list[i].path, PATH.STAGE.FREE+screenFreePlayInit.allPlaylist.list[i].path+'/listimg.png', 100, 100);
    }
    // Load BGM
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmSelectAccount.mod');
  },
  create: function(){

    // Play BGM
    C2TrackerControl.play(C2Trackers.bgmLoop);

    // Playlist Init
    this.var.allPlaylist = screenFreePlayInit.allPlaylist;
    this.var.currentPlaylist.init(this.var.allPlaylist);

    // Image Init
    this.img.background = game.add.sprite(0, 0, 'background');
    this.img.songselector= game.add.sprite(10, 90, 'songselector');
    this.img.patternselector = game.add.sprite(150, 135, 'patternselector');
    this.img.songimg = game.add.sprite(150, 30, this.var.allPlaylist.list[0].path, 0);

    this.button.option = game.add.button(
      150, 170, 'option', this.buttonOption, this);
    this.button.backspace = game.add.button(
      10, 10, 'backspacebutton', this.buttonBackspace, this);
    this.button.help = game.add.button(
      295, 10, 'helpbutton', this.buttonHelp, this);
    this.button.start = game.add.button(
      260, 135, 'startbutton', this.buttonStart, this);

    this.button.song0 = game.add.button(
      10,  30, 'invisible', this.buttonSong0, this);
    this.button.song0.width=120;
    this.button.song0.height=20;

    this.button.song1 = game.add.button(
      10,  50, 'invisible', this.buttonSong1, this);
    this.button.song1.width=120;
    this.button.song1.height=20;

    this.button.song2 = game.add.button(
      10,  70, 'invisible', this.buttonSong2, this);
    this.button.song2.width=120;
    this.button.song2.height=20;

    this.button.song3 = game.add.button(
      10, 110, 'invisible', this.buttonSong3, this);
    this.button.song3.width=120;
    this.button.song3.height=20;

    this.button.song4 = game.add.button(
      10, 130, 'invisible', this.buttonSong4, this);
    this.button.song4.width=120;
    this.button.song4.height=20;

    this.button.song5 = game.add.button(
      10, 150, 'invisible', this.buttonSong5, this);
    this.button.song5.width=120;
    this.button.song5.height=20;

    this.button.pattern0 = game.add.button(
      150, 135, 'invisible', this.buttonPattern0, this);
    this.button.pattern0.width= 30;
    this.button.pattern0.height=30;

    this.button.pattern1 = game.add.button(
      185, 135, 'invisible', this.buttonPattern1, this);
    this.button.pattern1.width= 30;
    this.button.pattern1.height=30;

    this.button.pattern2 = game.add.button(
      220, 135, 'invisible', this.buttonPattern2, this);
    this.button.pattern2.width= 30;
    this.button.pattern2.height= 30;

    // Text Init
    for(var i=0; i<7; i++){
      this.text.song.push({
        title: "",
        level: "",
        bpm: ""
      });
      this.text.song[i].title = game.add.bitmapText(15, 31+i*20, 'font57', this.var.currentPlaylist.list[i].name, 7);
      this.text.song[i].level = game.add.bitmapText(65, 41+i*20, 'font57', 'LV.' + this.var.currentPlaylist.list[i].level[this.var.selectedPattern]+' / ', 7);
      this.text.song[i].bpm = game.add.bitmapText(95, 41+i*20, 'font57', 'BPM ' + this.var.currentPlaylist.list[i].tempo, 7);
    }

    this.text.screenTitle = game.add.bitmapText(30, 10, 'font79', this.string.screenTitle, 9);





    // Option Panel Init
    this.img.optionWindow = game.add.sprite(150, 180, 'optionWindow');
    this.img.optionselector = game.add.sprite(160, 180, 'optionselector');

    this.text.optionTitle = game.add.bitmapText(160, 36, 'font79', '', 9);
    this.text.speedTitle = game.add.bitmapText(170, 48, 'font79', '', 9);
    this.text.skinTitle = game.add.bitmapText(170, 88, 'font79', '', 9);
    this.text.noteTitle = game.add.bitmapText(170, 128, 'font79', '', 9);

    this.text.speedValue = game.add.bitmapText(190, 66, 'font79', '', 9);

    this.flag.start = false;
  },

  update: function(){
    if(!this.flag.start){
      this.selectionUpdate();
      this.flag.start = true;
    }

    if(this.flag.optionWindow){
      if (game.input.keyboard.justPressed(RGinput.menu.keyCancel) ||
        game.input.keyboard.justPressed(RGinput.menu.keyOption1) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padCancel)||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padOption1)){
        this.pressoption();
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyUP) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padUP)){
        this.moveOptionSelector('up');
        console.log('option up ' + this.var.selectedOptionNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyDOWN) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padDOWN)){
        this.moveOptionSelector('down');
        console.log('option down ' + this.var.selectedOptionNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyLEFT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padLEFT)){
        console.log('option left');
        this.moveOptionSelector('left');
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyRIGHT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padRIGHT)){
        console.log('option right');
        this.moveOptionSelector('right');
      }
    }
    else{
      if (game.input.keyboard.justPressed(RGinput.menu.keyCancel) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padCancel)){
        this.pressbackspace();
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyOption1) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padOption1)){
        this.pressoption();
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyUP) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padUP)){
        this.moveSongSelector('up', 1);
        console.log('up ' + this.var.selectedSongNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyDOWN) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padDOWN)){
        this.moveSongSelector('down', 1);
        console.log('down ' + this.var.selectedSongNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyLEFT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padLEFT)){
        console.log('left');
        this.movePatternSelector('left');
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyRIGHT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padRIGHT)){
        console.log('right');
        this.movePatternSelector('right');
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyOK) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padOK)){
        console.log('start');
        this.pressstart();
      }
    }
  },
  buttonBackspace: function(pointer, isOver){
    if(this.flag.optionWindow){

    }
    else{
      if (isOver) this.pressbackspace();
    }
  },
  buttonHelp: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if (isOver) this.presshelp();}
  },
  buttonStart: function( pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if (isOver) this.pressstart();}
  },
  buttonOption: function(pointer, isOver){
    if (isOver) this.pressoption();
  },

  buttonSong0: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('up', 3);}
  },
  buttonSong1: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('up', 2);}
  },
  buttonSong2: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('up', 1);}
  },
  buttonSong3: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('down', 1);}
  },
  buttonSong4: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('down', 2);}
  },
  buttonSong5: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveSongSelector('down', 3);}
  },
  buttonPattern0: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
    {if(isOver) this.movePatternSelector(0);}
  },
  buttonPattern1: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
    {if(isOver) this.movePatternSelector(1);}
  },
  buttonPattern2: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
    {if(isOver) this.movePatternSelector(2);}
  },
  buttonSpeedL: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=0;
      this.updateOptionWindowPos();
    }
  },
  buttonSpeedR: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=0;
      this.updateOptionWindowPos();
    }
  },
  buttonSkinL: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=1;
      this.updateOptionWindowPos();
    }
  },
  buttonSkinR: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=1;
      this.updateOptionWindowPos();
    }
  },
  buttonNoteL: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=2;
      this.updateOptionWindowPos();
    }
  },
  buttonNoteR: function(pointer, isOver){
    if(this.flag.optionWindow && isOver){
      this.var.selectedOptionNum=2;
      this.updateOptionWindowPos();
    }
  },

  movePatternSelector: function(selection) {
    switch(selection){
    case 0:
    case 1:
    case 2:
      this.var.selectedPattern = selection;
      break;
    case 'right':
      if(this.var.selectedPattern >= 2){
        this.var.selectedPattern = 0;
      }
      else {
        this.var.selectedPattern++;
      }
      break;
    case 'left':
      if(this.var.selectedPattern <= 0){
        this.var.selectedPattern = 2;
      }
      else {
        this.var.selectedPattern--;
      }
      break;
    }
    this.selectionUpdate();
  },

  moveSongSelector: function(selection, repeat) {
    if(!(repeat == 1 || repeat == 2 || repeat == 3)) return -1;
    for(var i=0; i<repeat; i++){
    switch(selection){
    case 'up':
      if(this.var.selectedSongNum > 0){
        this.var.selectedSongNum --;
      }
      else {
        this.var.selectedSongNum = this.var.allPlaylist.max-1;
      }
      break;
    case 'down':
      if(this.var.selectedSongNum < this.var.allPlaylist.max-1){
        this.var.selectedSongNum ++;
      }
      else {
        this.var.selectedSongNum = 0;
      }
      break;
    default:
    }
    }
    this.selectionUpdate();
  },

  moveOptionSelector: function(selection) {
    switch(selection){
    case 'up':
      if(this.var.selectedOptionNum <= 0){
        this.var.selectedOptionNum = 2;
      }
      else{
        this.var.selectedOptionNum--;
      }
      break;
    case 'down':
      if(this.var.selectedOptionNum >= 2){
        this.var.selectedOptionNum = 0;
      }
      else{
        this.var.selectedOptionNum++;
      }
      break;
    case 'left':
      switch(this.var.selectedOptionNum){
      case 0:
        if(this.var.selectedSpeedNum <= 1){
          this.var.selectedSpeedNum = 48;
        }
        else{
          this.var.selectedSpeedNum--;
        }
        this.var.selectedSpeedValue = this.var.selectedSpeedNum*25;
        break;
      case 1:
        break;
      case 2:
        break;
      }
      break;
    case 'right':
      switch(this.var.selectedOptionNum){
      case 0:
        if(this.var.selectedSpeedNum >= 48){
          this.var.selectedSpeedNum = 1;
        }
        else{
          this.var.selectedSpeedNum++;
        }
        this.var.selectedSpeedValue = this.var.selectedSpeedNum*25;
        break;
      case 1:
        break;
      case 2:
        break;
      }
      break;
    }
    this.selectionUpdate();
  },

  setCurrentPlaylist: function(index) {
    this.var.currentPlaylist.update(this.var.allPlaylist, index);
    for(var i=0; i<7; i++){
      this.text.song[i].title.setText(this.var.currentPlaylist.list[i].name);
      this.text.song[i].level.setText('LV.'+this.var.currentPlaylist.list[i].level[this.var.selectedPattern]);
      this.text.song[i].bpm.setText('BPM ' + this.var.currentPlaylist.list[i].tempo, 7);
    }
    this.img.songimg.loadTexture(this.var.allPlaylist.list[this.var.selectedSongNum].path);
    this.img.songimg.frame=this.var.selectedPattern;

  },
  sortByTitle: function(){
  },

  sortByLevel: function(pattern){
  },

  pressoption: function(){
    this.flag.optionWindow = !this.flag.optionWindow;
    this.selectionUpdate();
  },

  pressbackspace: function(){
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    game.state.start('screenLobby');
  },

  presshelp: function(){
    console.log('presshelp()');
  },

  pressstart: function(){
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    PATH.setStage(
      this.var.allPlaylist.list[this.var.selectedSongNum].path,
      this.var.selectedPattern);
    screenPlay.var.speed = this.var.selectedSpeedValue;
    game.state.start('screenPlayInit');
  },

  selectionUpdate: function(){
    if(this.flag.optionWindow){
      this.img.optionWindow.y = 30;
      this.img.optionselector.y = 60 + 40*this.var.selectedOptionNum;
      this.text.optionTitle.setText(this.string.optionTitle);
      this.text.speedTitle.setText(this.string.speedTitle);
      this.text.skinTitle.setText(this.string.skinTitle);
      this.text.noteTitle.setText(this.string.noteTitle);
      this.text.speedValue.setText(this.var.selectedSpeedValue);
    }
    else{
      this.text.optionTitle.setText('');
      this.text.speedTitle.setText('');
      this.text.skinTitle.setText('');
      this.text.noteTitle.setText('');
      this.text.speedValue.setText('');
      this.img.optionselector.y = 180;
      this.img.optionWindow.y = 180;
    }
    this.setCurrentPlaylist(this.var.selectedSongNum);
    this.img.patternselector.x = 150 + 35 * this.var.selectedPattern;
  }
};
