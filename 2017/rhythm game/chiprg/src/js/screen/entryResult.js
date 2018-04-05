var screenEntryResult = {
  name: "screenEntryResult",
  var: {
    songGenre: "",
    songTitle: "",
    songArtist: "",
    songPattern: "",
    songLevel: "",
    score: "",
    advScore: "",
    judgeData: "",
    lastCombo: "",
    maxCombo: "",
    total: "",
    gradeRate: "",
    isAllCombo: "",
    isAllGreat: "",
    isAllPerfect: "",
    totalScore:"",
    getResultData: function(){
      this.songGenre = Stagedata.genre;
      this.songTitle = Stagedata.title;
      this.songArtist = Stagedata.artist;
      this.songPattern = Stagedata.pattern;
      this.songLevel = Stagedata.songLevel;
      this.score = screenPlay.var.score.value;
      this.advScore = screenPlay.var.score.advanced;
      this.judgeData = screenPlay.var.score.judgeData;
      this.lastCombo = screenPlay.var.combo.value;
      this.maxCombo = screenPlay.var.combo.max;
      this.total = screenPlay.var.total;
      this.gradeRate = this.score / (this.total*10);
      this.isAllCombo = screenPlay.var.score.isAllCombo();
      this.isAllGreat = screenPlay.var.score.isAllGreat();
      this.isAllPerfect = screenPlay.var.score.isAllPerfect();
      if(this.isAllGreat === true){
        this.totalScore = screenPlay.var.score.value+
                        screenPlay.var.score.advanced;
      }
      else{
        this.totalScore = screenPlay.var.score.value;
      }
    },
    isCleared: function(){
      if(screenPlay.var.lifeGague.value > 0) return true;
      else return false;
    },
  },
  string: {
    screenTitle: function(){
      switch(screenEntryResult.var.isCleared()){
      case true:
        return "STAGE CLEAR";
      case false:
        return "STAGE FAILED";
      }
    },
    bestRecord:[
      "BEST RECORD"
    ],
    rank:[ "1ST PLACE", "2ND PLACE", "3RD PLACE", "4TH PLACE", "5TH PLACE" ],
    grade: "GRADE",
    gradeValue: function(){
      if(screenEntryResult.var.gradeRate>=98)      return 'SS';
      else if(screenEntryResult.var.gradeRate>=95) return 'S';
      else if(screenEntryResult.var.gradeRate>=90) return 'A';
      else if(screenEntryResult.var.gradeRate>=80) return 'B';
      else if(screenEntryResult.var.gradeRate>=70) return 'C';
      else if(screenEntryResult.var.gradeRate>=50) return 'D';
      else                                   return 'F';
    },
    isAll: function(){
      if(screenEntryResult.var.isAllPerfect)
        return 'ALL PERFECT';
      else if(screenEntryResult.var.isAllGreat)
        return 'ALL GREAT';
      else if(screenEntryResult.var.isAllCombo)
        return 'ALL COMBO';
      else
        return '';
    },

    total      : "TOTAL NOTE  : ",
    maxCombo   : "MAX COMBO   : ",
    perfect    : "PERFECT     : ",
    great      : "GREAT       : ",
    good       : "GOOD        : ",
    miss       : "MISS        : ",
    bad        : "BAD         : ",
    fail       : "FAIL        : ",
    score      : "SCORE       : ",
    totalScore : "TOTAL SCORE : ",
    advBonus: "ALL GREAT BONUS",

    lobby: "LOBBY",
    nextEntry: "PLAY NEXT ENTRY",
  },
  text: {
    screenTitle: "",
    songGenre: "",
    songTitle: "",
    songArtist: "",
    songPattern: "",
    songLevel: "",
    songLength: "",

    bestRecord: "",
    rank: "",
    grade: "",
    gradeValue: "",

    total: "",
    score: "",
    totalScore: "",
    advBonus: "",
    judgeData: {
      perfect: "",
      great: "",
      good: "",
      miss: "",
      bad: "",
      fail: ""
    },
    maxCombo: "",
    isAll: "",
    button: "",
  },


  img: {
    background: "",
    selector1:"",
    selector2:"",
    rank:"",
    isAll:"",

    button1: "",
    button2: "",
    button3: ""
  },

  title: "",
  preload: function(){
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
    game.load.image('background', this.uiPath+'background.png');
    game.load.image('buttonLong', this.uiPath+'buttonLong.png');
    game.load.image('buttonShort', this.uiPath+'buttonShort.png');
  },
  create: function(){
    this.var.getResultData();
    this.img.background = game.add.sprite(0, 0, 'background');

    this.img.button3 = game.add.button(190, 150, 'buttonLong',
      this.button3touched, this);

    this.text.screenTitle = game.add.bitmapText(
      10, 11, 'font79', this.string.screenTitle(), 9);
    this.text.songTitle = game.add.bitmapText(
      20, 37, 'font57', this.var.songTitle, 7);
    this.text.songPattern = game.add.bitmapText(
      130, 37, 'font57', 'LV.'+this.var.songLevel+' '+this.var.songPattern, 7);
    this.text.total = game.add.bitmapText(
      20, 56, 'font57', this.string.total+
      SomeMath.pad0(this.var.total, 4, 0), 7);
    this.text.maxCombo = game.add.bitmapText(
      20, 66, 'font57', this.string.maxCombo+
      SomeMath.pad0(this.var.maxCombo, 4, 0), 7);
    this.text.perfect = game.add.bitmapText(
      20, 81, 'font57', this.string.perfect+
      SomeMath.pad0(this.var.judgeData.perfect, 4, 0), 7);
    this.text.great = game.add.bitmapText(
      20, 91, 'font57', this.string.great+
      SomeMath.pad0(this.var.judgeData.great, 4, 0), 7);
    this.text.good = game.add.bitmapText(
      20,101, 'font57', this.string.good+
      SomeMath.pad0(this.var.judgeData.good, 4, 0), 7);
    this.text.bad = game.add.bitmapText(
      20,111, 'font57', this.string.bad+
      SomeMath.pad0(this.var.judgeData.bad, 4, 0), 7);
    this.text.fail = game.add.bitmapText(
      20,121, 'font57', this.string.fail+
      SomeMath.pad0(this.var.judgeData.fail, 4, 0), 7);
    this.text.miss = game.add.bitmapText(
      20,131, 'font57', this.string.miss+
      SomeMath.pad0(this.var.judgeData.miss, 4, 0), 7);
    this.text.score = game.add.bitmapText(
      20,145, 'font57', this.string.score+
      SomeMath.pad0(this.var.score, 7, 0)+
      '', 7);
    this.text.totalScore = game.add.bitmapText(
      20,155, 'font57', '', 7);

    this.text.grade = game.add.bitmapText(
      115, 56, 'font57', this.string.grade, 7);
    this.text.gradeValue = game.add.bitmapText(
      110, 62, 'font79', this.string.gradeValue(), 45);

    this.text.isAll = game.add.bitmapText(
      125, 104, 'font57', this.string.isAll(), 7);

    if(this.var.isCleared()){
      this.text.nextEntry = game.add.bitmapText(
        215, 157, 'font57', this.string.nextEntry, 7);
    }
    else{
      this.text.lobby = game.add.bitmapText(
        215, 157, 'font57', this.string.lobby, 7);
    }
    this.writeEntryResultData(screenCourseInit.var.currentEntry);

  },
  writeEntryResultData: function(entryNum){
    CourseResultData.entry[entryNum].score = this.var.totalScore;
    CourseResultData.entry[entryNum].gradeRate = this.var.gradeRate;
    CourseResultData.entry[entryNum].gradeValue = this.string.gradeValue();
    CourseResultData.entry[entryNum].isAll = this.string.isAll();
  },
  update: function(){
    if(this.var.isAllGreat) {
      this.text.score.setText(
        this.string.score+
        SomeMath.pad0(this.var.score, 7, 0)+' + '+
        SomeMath.pad0(this.var.advScore, 6, 0));
      this.text.totalScore.setText(
        this.string.totalScore+
        SomeMath.pad0(this.var.totalScore, 8, 0));
    }
  },

  button3touched: function(){
    if(this.var.isCleared())
      this.nextEntry();
    else
      this.lobby();
  },
  lobby: function() {
    screenCourseInit.var.currentEntry=0;
    screenCourseInit.var.isCoursePlay=0;
    game.state.start('screenLobby');
  },
  nextEntry: function() {
    screenCourseInit.var.currentEntry++;
    game.state.start('screenCourseInit');
  }
};