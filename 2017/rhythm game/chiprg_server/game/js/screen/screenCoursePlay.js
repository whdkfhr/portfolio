var screenCoursePlay = {
  name: "screenCoursePlay",
  uiPath: "",

  string: {
    screenTitle: "COURSE PLAY",
    optionTitle: "OPTION",
    speedTitle: "SPEED",
    skinTitle: "SKIN",
    noteTitle: "NOTE",
    viewImg: "VIEW IMAGE",
    viewEntry: "VIEW ENTRY"
  },

  text: {
    screenTitle: "",
    course: [],
    optionTitle: "",
    speedTitle: "",
    skinTitle: "",
    noteTitle: "",
    viewImg: "",
    viewEntry: "",
    entry: [
      {title: "", tempo: ""},
      {title: "", tempo: ""},
      {title: "", tempo: ""},
      {title: "", tempo: ""}
    ],

    speedValue: ""
  },

  img: {
    background: "",
    courseselector: "",
    viewselector: "",
    courseimg: "",

    optionselector: "",
    speed: "",
    skin: "",
    note: "",
  },
  button: {
    view0: "",
    view1: "",

    course0: "",
    course1: "",
    course2: "",
    course3: "",
    course4: "",
    course5: "",

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
    selectedCourseNum: 0,
    selectedCourseName: "",
    selectedView: 0,
    allCourseList: "",
    currentCourseList: {
      list: [],
      init: function(allCourseList){
        this.update(allCourseList, 0);
      },
      update: function(allCourseList, selected){
        for(var i=0; i<7; i++){
          var j = SomeMath.modulo((i-3 + selected), allCourseList.max);
          this.list[i] = allCourseList.list[j];
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
    game.load.image('viewselector', this.uiPath+'viewselector.png');
    game.load.image('courseselector', this.uiPath+'courseselector.png');
    game.load.image('startbutton', this.uiPath+'start.png',110,23);
    game.load.image('optionWindow', this.uiPath+'optionWindow.png');
    game.load.image('invisible', this.uiPath+'invisible.png');
    game.load.image('optionselector', this.uiPath+'optionselector.png');

    for(var i=0; i<screenCoursePlayInit.allCourseList.max; i++){
      game.load.spritesheet(screenCoursePlayInit.allCourseList.list[i].path, PATH.STAGE.COURSE+screenCoursePlayInit.allCourseList.list[i].path+'/listimg.png', 100, 100);
    }
    // Load BGM
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmSelectAccount.mod');
  },
  create: function(){

    // Play BGM
    C2TrackerControl.play(C2Trackers.bgmLoop);

    // Playlist Init
    this.var.allCourseList = screenCoursePlayInit.allCourseList;
    this.var.currentCourseList.init(this.var.allCourseList);

    // Image Init
    this.img.background = game.add.sprite(0, 0, 'background');
    this.img.courseselector= game.add.sprite(10, 90, 'courseselector');
    this.img.viewselector = game.add.sprite(150, 135, 'viewselector');
    this.img.courseimg = game.add.sprite(150, 30, this.var.allCourseList.list[0].path, 0);

    this.button.option = game.add.button(
      150, 170, 'option', this.buttonOption, this);
    this.button.backspace = game.add.button(
      10, 10, 'backspacebutton', this.buttonBackspace, this);
    this.button.help = game.add.button(
      295, 10, 'helpbutton', this.buttonHelp, this);
    this.button.start = game.add.button(
      260, 135, 'startbutton', this.buttonStart, this);

    this.button.course0 = game.add.button(
      10,  30, 'invisible', this.buttonCourse0, this);
    this.button.course0.width=120;
    this.button.course0.height=20;

    this.button.course1 = game.add.button(
      10,  50, 'invisible', this.buttonCourse1, this);
    this.button.course1.width=120;
    this.button.course1.height=20;

    this.button.course2 = game.add.button(
      10,  70, 'invisible', this.buttonCourse2, this);
    this.button.course2.width=120;
    this.button.course2.height=20;

    this.button.course3 = game.add.button(
      10, 110, 'invisible', this.buttonCourse3, this);
    this.button.course3.width=120;
    this.button.course3.height=20;

    this.button.course4 = game.add.button(
      10, 130, 'invisible', this.buttonCourse4, this);
    this.button.course4.width=120;
    this.button.course4.height=20;

    this.button.course5 = game.add.button(
      10, 150, 'invisible', this.buttonCourse5, this);
    this.button.course5.width=120;
    this.button.course5.height=20;

    this.button.view0 = game.add.button(
      150, 135, 'invisible', this.buttonView0, this);
    this.button.view0.width= 48;
    this.button.view0.height=20;

    this.button.view1 = game.add.button(
      185, 135, 'invisible', this.buttonView1, this);
    this.button.view1.width= 48;
    this.button.view1.height=20;

    // Text Init
    for(var i=0; i<7; i++){
      this.text.course.push({
        title: "",
        level: "",
        bpm: ""
      });
      this.text.course[i].title = game.add.bitmapText(15, 31+i*20, 'font57', this.var.currentCourseList.list[i].name, 7);
      this.text.course[i].level = game.add.bitmapText(65, 41+i*20, 'font57', 'LV.' + this.var.currentCourseList.list[i].level, 7);
    }

    this.text.viewImg = game.add.bitmapText(153, 141,
      'font57', this.string.viewImg, 7);
    this.text.viewEntry = game.add.bitmapText(205, 141,
      'font57', this.string.viewEntry, 7);

    for(var j=0; j<4; j++){
      this.text.entry[j].title = game.add.bitmapText(155, 41+j*20, 'font57',this.var.allCourseList.list[this.var.selectedCourseNum].entry[j].title, 7);
      this.text.entry[j].tempo = game.add.bitmapText(230, 51+j*20, 'font57',this.var.allCourseList.list[this.var.selectedCourseNum].entry[j].tempo, 7);

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
        this.moveCourseSelector('up', 1);
        console.log('up ' + this.var.selectedCourseNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyDOWN) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padDOWN)){
        this.moveCourseSelector('down', 1);
        console.log('down ' + this.var.selectedCourseNum);
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyLEFT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padLEFT)){
        console.log('left');
        this.moveViewSelector('left');
      }
      if (game.input.keyboard.justPressed(RGinput.menu.keyRIGHT) ||
        game.input.gamepad.pad1.justPressed(RGinput.menu.padRIGHT)){
        console.log('right');
        this.moveViewSelector('right');
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

  buttonCourse0: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('up', 3);}
  },
  buttonCourse1: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('up', 2);}
  },
  buttonCourse2: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('up', 1);}
  },
  buttonCourse3: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('down', 1);}
  },
  buttonCourse4: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('down', 2);}
  },
  buttonCourse5: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
      {if(isOver) this.moveCourseSelector('down', 3);}
  },
  buttonView0: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
    {if(isOver) this.moveViewSelector(0);}
  },
  buttonView1: function(pointer, isOver){
    if(this.flag.optionWindow){}
    else
    {if(isOver) this.moveViewSelector(1);}
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

  moveViewSelector: function(selection) {
    switch(selection){
    case 0:
    case 1:
      this.var.selectedView = selection;
      break;
    case 'right':
      if(this.var.selectedView >= 1){
        this.var.selectedView = 0;
      }
      else {
        this.var.selectedView++;
      }
      break;
    case 'left':
      if(this.var.selectedView <= 0){
        this.var.selectedView = 1;
      }
      else {
        this.var.selectedView--;
      }
      break;
    }
    this.selectionUpdate();
  },

  moveCourseSelector: function(selection, repeat) {
    if(!(repeat == 1 || repeat == 2 || repeat == 3)) return -1;
    for(var i=0; i<repeat; i++){
    switch(selection){
    case 'up':
      if(this.var.selectedCourseNum > 0){
        this.var.selectedCourseNum --;
      }
      else {
        this.var.selectedCourseNum = this.var.allCourseList.max-1;
      }
      break;
    case 'down':
      if(this.var.selectedCourseNum < this.var.allCourseList.max-1){
        this.var.selectedCourseNum ++;
      }
      else {
        this.var.selectedCourseNum = 0;
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
    this.var.currentCourseList.update(this.var.allCourseList, index);
    for(var i=0; i<7; i++){
      this.text.course[i].title.setText(this.var.currentCourseList.list[i].name);
      this.text.course[i].level.setText('LV.'+this.var.currentCourseList.list[i].level);
    }
    switch(this.var.selectedView){
    case 0:
      for(var k=0; k<4; k++){
        this.text.entry[k].title.setText('');
        this.text.entry[k].tempo.setText('');
      }
      this.img.courseimg.loadTexture(this.var.allCourseList.list[this.var.selectedCourseNum].path);
      break;
    case 1:
      for(var j=0; j<4; j++){
        this.text.entry[j].title.setText(
          this.var.allCourseList.list[this.var.selectedCourseNum].entry[j].title);
        this.text.entry[j].tempo.setText(
          this.var.allCourseList.list[this.var.selectedCourseNum].entry[j].tempo);
      }
      this.img.courseimg.loadTexture('invisible');
      break;
    }


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
    PATH.setCourse(
      this.var.allCourseList.list[this.var.selectedCourseNum].path);
    screenPlay.var.speed = this.var.selectedSpeedValue;
    game.state.start('screenCourseInit');
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
    this.setCurrentPlaylist(this.var.selectedCourseNum);
    this.img.viewselector.x = 150 + 52 * this.var.selectedView;
  }
};
