var screenRanking = {
  name: "screenRanking",
  uiPath: "",

  string: {
    screenTitle: "RANKING",
    userID: "USER ID",
    score: "SCORE"
  },

  text: {
    screenTitle: "",
    list: [],
    ranking: [],
    rankingGuide: ""
  },

  img: {
    background: "",
    modeSelector: "",
    patternSelector: "",
  },
  button: {
    pattern0: "",
    pattern1: "",
    pattern2: "",

    list0: "",
    list1: "",
    list2: "",
    list3: "",
    list4: "",
    list5: "",

    backspace: "",
    help: "",
    search: "",
    inputName: "",
  },
  var: {
    start: false,

    selectedListNum: 0,
    selectedListName: "",
    selectedListID: "",
    selectedPattern: 0,

    selectedMode: 0,

    freePlaylist: "",
    coursePlaylist: "",
    selectedModeList: "",

    currentPlaylist: {
      list: [],
      init: function(playlist){
        this.update(playlist, 0);
      },
      update: function(playlist, selected){
        for(var i=0; i<7; i++){
          var j = SomeMath.modulo((i-3 + selected), playlist.max);
          this.list[i] = playlist.list[j];
        }
      }
    },
  },

  preload: function(){

    // Load Images
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
    game.load.image('background', this.uiPath+'background.png');
    game.load.image('backspacebutton', this.uiPath+'backspace.png');
    game.load.image('helpbutton', this.uiPath+'help.png');
    game.load.spritesheet('patternSelector', this.uiPath+'patternSelector.png', 45, 20);
    game.load.spritesheet('modeSelector', this.uiPath+'modeSelector.png', 20, 140);
    game.load.image('invisible', this.uiPath+'invisible.png');

    // Load BGM
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmSelectAccount.mod');
  },
  create: function(){
    // Play BGM
    C2TrackerControl.play(C2Trackers.bgmLoop);

    // Playlist Init
    this.var.currentPlaylist.init(screenRankingInit.freePlaylist);

    // Image Init
    this.img.background = game.add.sprite(0, 0, 'background');
    this.img.modeSelector= game.add.button(
      10, 30, 'modeSelector', this.modeToggle, this);
    this.img.patternSelector = game.add.sprite(135, 90, 'patternSelector');

    this.button.backspace = game.add.button(
      10, 10, 'backspacebutton', this.buttonBackspace, this);
    this.button.help = game.add.button(
      295, 10, 'helpbutton', this.buttonHelp, this);
    this.button.search = game.add.button(
      180, 150, 'invisible', this.buttonSearch, this);
    this.text.search = game.add.bitmapText(
      210, 155, 'font79', 'SEARCH', 9);
    this.button.search.width = 130;
    this.button.search.height = 20;
    

    this.button.list0 = game.add.button(
      30,  30, 'invisible', this.buttonList0, this);
    this.button.list0.width=150;
    this.button.list0.height=20;

    this.button.list1 = game.add.button(
      30,  50, 'invisible', this.buttonList1, this);
    this.button.list1.width=150;
    this.button.list1.height=20;

    this.button.list2 = game.add.button(
      30,  70, 'invisible', this.buttonList2, this);
    this.button.list2.width=150;
    this.button.list2.height=20;

    this.button.list3 = game.add.button(
      30, 110, 'invisible', this.buttonList3, this);
    this.button.list3.width=150;
    this.button.list3.height=20;

    this.button.list4 = game.add.button(
      30, 130, 'invisible', this.buttonList4, this);
    this.button.list4.width=150;
    this.button.list4.height=20;

    this.button.list5 = game.add.button(
      30, 150, 'invisible', this.buttonList5, this);
    this.button.list5.width=150;
    this.button.list5.height=20;

    this.button.pattern0 = game.add.button(
      135, 90, 'invisible', this.buttonPattern0, this);
    this.button.pattern0.width= 20;
    this.button.pattern0.height=20;

    this.button.pattern1 = game.add.button(
      150, 90, 'invisible', this.buttonPattern1, this);
    this.button.pattern1.width= 20;
    this.button.pattern1.height=20;

    this.button.pattern2 = game.add.button(
      165, 90, 'invisible', this.buttonPattern2, this);
    this.button.pattern2.width= 20;
    this.button.pattern2.height= 20;

    // Text Init
    for(var i=0; i<7; i++){
      this.text.list.push({
        title: "",
        ez: "",
        nm: "",
        hd: ""
      });
      this.text.list[i].title = game.add.bitmapText(35, 31+i*20, 'font57', 
        this.var.currentPlaylist.list[i].name, 7);
      if(i==3){
        this.text.list[i].ez    = game.add.bitmapText(138, 40+i*20, 'font57', 
          SomeMath.pad0(this.var.currentPlaylist.list[i].level[0], 2, ' '), 7);
        this.text.list[i].nm    = game.add.bitmapText(153, 40+i*20, 'font57', 
          SomeMath.pad0(this.var.currentPlaylist.list[i].level[1], 2, ' '), 7);
        this.text.list[i].hd    = game.add.bitmapText(168, 40+i*20, 'font57', 
          SomeMath.pad0(this.var.currentPlaylist.list[i].level[2], 2, ' '), 7);
      }
    }
    
    this.text.rankingGuide = game.add.bitmapText(181, 31,      'font57', 
      '    ID           SCORE    DATE  ', 7);
    for(var j=0; j<11; j++){
      this.text.ranking[j] = game.add.bitmapText(181, 41+j*10, 'font57', 
      '                              ', 7);
    }

    this.text.screenTitle = game.add.bitmapText(30, 10, 'font79', this.string.screenTitle, 9);

    this.var.selectedModeList = screenRankingInit.freePlaylist;
    this.selectionUpdate(this.var.selectedModeList);
  },

  update: function(){
    if (game.input.keyboard.justPressed(RGinput.menu.keyCancel) ||
      game.input.gamepad.pad1.justPressed(RGinput.menu.padCancel)){
      this.pressbackspace();
    }
    if (game.input.keyboard.justPressed(RGinput.menu.keyUP) ||
      game.input.gamepad.pad1.justPressed(RGinput.menu.padUP)){
      this.moveListSelector('up', 1, this.var.selectedModeList);
      console.log('up ' + this.var.selectedListNum);
    }
    if (game.input.keyboard.justPressed(RGinput.menu.keyDOWN) ||
      game.input.gamepad.pad1.justPressed(RGinput.menu.padDOWN)){
      this.moveListSelector('down', 1, this.var.selectedModeList);
      console.log('down ' + this.var.selectedListNum);
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
      console.log('search');
      this.pressSearch();
    }
    if (game.input.keyboard.justPressed(RGinput.menu.keyOption1) ||
      game.input.gamepad.pad1.justPressed(RGinput.menu.padOption1)){
      console.log('toggle');
      this.modeToggle();
    }
  },
  buttonBackspace: function(pointer, isOver){

    if (isOver) this.pressbackspace();

  },
  buttonHelp: function(pointer, isOver){
    if (isOver) this.presshelp();
  },
  buttonSearch: function( pointer, isOver){
    if (isOver) this.pressSearch();
  },

  buttonList0: function(pointer, isOver){
    if(isOver) this.moveListSelector('up', 3, this.var.selectedModeList);
  },
  buttonList1: function(pointer, isOver){
    if(isOver) this.moveListSelector('up', 2, this.var.selectedModeList);
  },
  buttonList2: function(pointer, isOver){
    if(isOver) this.moveListSelector('up', 1, this.var.selectedModeList);
  },
  buttonList3: function(pointer, isOver){
    if(isOver) this.moveListSelector('down', 1, this.var.selectedModeList);
  },
  buttonList4: function(pointer, isOver){
    if(isOver) this.moveListSelector('down', 2, this.var.selectedModeList);
  },
  buttonList5: function(pointer, isOver){
    if(isOver) this.moveListSelector('down', 3, this.var.selectedModeList);
  },
  buttonPattern0: function(pointer, isOver){
    if(isOver) this.movePatternSelector(0);
  },
  buttonPattern1: function(pointer, isOver){
    if(isOver) this.movePatternSelector(1);
  },
  buttonPattern2: function(pointer, isOver){
    if(isOver) this.movePatternSelector(2);
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
    this.selectionUpdate(this.var.selectedModeList);
  },

  moveListSelector: function(selection, repeat, list) {
    if(!(repeat == 1 || repeat == 2 || repeat == 3)) return -1;
    for(var i=0; i<repeat; i++){
    switch(selection){
    case 'up':
      if(this.var.selectedListNum > 0){
        this.var.selectedListNum --;
      }
      else {
        this.var.selectedListNum = list.max-1;
      }
      break;
    case 'down':
      if(this.var.selectedListNum < list.max-1){
        this.var.selectedListNum ++;
      }
      else {
        this.var.selectedListNum = 0;
      }
      break;
    default:
    }
    }
    this.selectionUpdate(list);
  },

  setCurrentPlaylist: function(index, list) {
    this.var.currentPlaylist.update(list, index);
    for(var i=0; i<7; i++){
      this.text.list[i].title.setText(this.var.currentPlaylist.list[i].name);
    }
    if(this.var.currentPlaylist.list[3].level[0] == undefined) {
      this.text.list[3].ez.setText('');
      this.text.list[3].nm.setText('');
      this.text.list[3].hd.setText('');
      this.img.patternSelector.frame = 3;
    }
    else {
      this.text.list[3].ez.setText(
        SomeMath.pad0(this.var.currentPlaylist.list[3].level[0], 2, ' '));
      this.text.list[3].nm.setText(
        SomeMath.pad0(this.var.currentPlaylist.list[3].level[1], 2, ' '));
      this.text.list[3].hd.setText(
        SomeMath.pad0(this.var.currentPlaylist.list[3].level[2], 2, ' '));
      this.img.patternSelector.frame = this.var.selectedPattern;
    }
  },
  
  pressbackspace: function(){
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    game.state.start('screenLobby');
  },

  presshelp: function(){
    console.log('presshelp()');
  },
  pressSearch: function(){
    console.log('pressSearch()');
    var query = new RGquery;
    if(this.var.selectedMode == 0){
      var ID = 
        screenRankingInit
        .freePlaylist
        .list[this.var.selectedListNum]
        .stageID[this.var.selectedPattern];
      console.log(ID);
      query.getFreeRanking(ID, undefined, 10, this.printRanking);
    }
    else if(this.var.selectedMode == 1){
      var ID = 
      screenRankingInit.coursePlaylist
      .list[this.var.selectedListNum]
      .courseID;
      console.log(ID);
      query.getCourseRanking(ID, undefined, 10, this.printRanking);
    }
  },
  selectionUpdate: function(list){
    this.setCurrentPlaylist(this.var.selectedListNum, list);
  },

  freePlayMode: function(){
    screenRanking.var.selectedModeList = screenRankingInit.freePlaylist;
    screenRanking.var.selectedMode = 0;
    this.selectionUpdate(screenRanking.var.selectedModeList);
  },
  coursePlayMode: function(){
    screenRanking.var.selectedModeList = screenRankingInit.coursePlaylist;
    screenRanking.var.selectedMode = 1;
    this.selectionUpdate(screenRanking.var.selectedModeList);
  },
  modeToggle: function(){
    this.var.selectedListNum = 0;
    switch(this.var.selectedMode){
    case 0:
      this.coursePlayMode();
      break;
    case 1:
      this.freePlayMode();
      break;
    }
    this.img.modeSelector.frame = this.var.selectedMode;
  },
  printRanking: function(rankingData){
    var length = rankingData.length;
    var date = {};
    var userName;
    var scoreString;
    var orderString = function(n){
      switch(n){
      case 0:
        return '1ST ';
      case 1:
        return '2ND ';
      case 2:
        return '3RD ';
      default:
        return JSON.stringify(n+1)+'TH ';
      }
    }

    for(var i=0; i<11; i++){
      if(i<rankingData.length){
        date.msec = new Date(rankingData[i].date);
        date.year = JSON.stringify(date.msec.getFullYear()).slice(2,4);
        date.month = SomeMath.pad0(date.msec.getMonth()+1, 2, 0);
        date.day = SomeMath.pad0(date.msec.getDate(), 2, 0);
        date.string = date.year+date.month+date.day;
        userName = SomeMath.paddRight(rankingData[i].userID, 12, ' ');
        scoreString = SomeMath.pad0(rankingData[i].score, 8, '0').slice(0,8);
        screenRanking.text.ranking[i].setText(orderString(i)+userName+' '+scoreString+' '+date.string);
      }
      else {
        screenRanking.text.ranking[i].setText(' ');
      }
    }
  }
};
