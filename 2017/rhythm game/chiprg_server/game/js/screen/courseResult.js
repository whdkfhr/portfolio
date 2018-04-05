var screenCourseResult = {
  rankingUploded: "",
  name: "screenCourseResult",
  string: {
    screenTitle: "COURSE ALL CLEAR",
    bestRecord:[
      "BEST RECORD"
    ],
    rank:[ "1ST PLACE", "2ND PLACE", "3RD PLACE", "4TH PLACE", "5TH PLACE" ],
    totalGrade: "GRADE",
    totalScore : "TOTAL SCORE",

    retry: "RETRY",
    lobby: "LOBBY",
    songSelect: "COURSE SELECT",
    postRanking: "POST RANKING"
  },
  text: {
    screenTitle: "",
    courseTitle: "",
    courseLevel: "",

    bestRecord: "",
    rank: "",
    totalGrade: "",
    totalGradeValue: "",
    totalScore: "",

    retry: "",
    lobby: "",
    songSelect: "",

    entry: [
      {
        title: "",
        score: "",
        grade: "",
        isAll: ""
      },
      {
        title: "",
        score: "",
        grade: "",
        isAll: ""
      },
      {
        title: "",
        score: "",
        grade: "",
        isAll: ""
      },
      {
        title: "",
        score: "",
        grade: "",
        isAll: ""
      },
    ],
  },


  img: {
    background: "",
    selector1:"",
    selector2:"",
    rank:"",
    isAll:"",

    button1: "",
    button2: "",
    button3: "",
    button4: ""
  },

  title: "",
  preload: function(){
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
    game.load.image('background', this.uiPath+'background.png');
    game.load.image('buttonLong', this.uiPath+'buttonLong.png');
    game.load.image('buttonShort', this.uiPath+'buttonShort.png');
  },
  create: function(){
    CourseResultData.calcTotal();
    this.img.background = game.add.sprite(0, 0, 'background');
    this.img.button1 = game.add.button(190, 125, 'buttonShort',
      this.button1touched, this);
    this.img.button2 = game.add.button(253, 125, 'buttonShort',
      this.button2touched, this);
    this.img.button3 = game.add.button(190, 150, 'buttonLong',
      this.button3touched, this);

    this.text.screenTitle = game.add.bitmapText(
      10, 11, 'font79', this.string.screenTitle, 9);
    this.text.courseTitle = game.add.bitmapText(
      20, 37, 'font57', CourseResultData.courseTitle, 7);
    this.text.songPattern = game.add.bitmapText(
      130, 37, 'font57', 'LV.'+CourseResultData.courseLevel, 7);

    for(var i=0; i<4; i++){
      this.text.entry[i].title = game.add.bitmapText(
        20, 57+i*30, 'font57', CourseResultData.entry[i].title, 7);
      this.text.entry[i].title = game.add.bitmapText(
        20, 67+i*30, 'font57', CourseResultData.entry[i].score, 7);
      this.text.entry[i].title = game.add.bitmapText(
        130, 54+i*30, 'font57', CourseResultData.entry[i].gradeValue, 14);
      this.text.entry[i].title = game.add.bitmapText(
        130, 70+i*30, 'font57', CourseResultData.entry[i].isAll, 7);
    }
    
    this.text.retry = game.add.bitmapText(
      210, 132, 'font57', this.string.retry, 7);
    this.text.lobby = game.add.bitmapText(
      272, 132, 'font57', this.string.lobby, 7);
    this.text.songSelect = game.add.bitmapText(
      215, 157, 'font57', this.string.songSelect, 7);

    this.text.totalScore = game.add.bitmapText(
      190, 107, 'font57', this.string.totalScore, 7);
    this.text.totalScoreVal = game.add.bitmapText(
      190, 113, 'font79', CourseResultData.totalScore, 9);
    this.text.totalGrade = game.add.bitmapText(
      190, 30, 'font57', this.string.totalGrade, 7);
    this.text.totalGradeVal = game.add.bitmapText(
      200, 36, 'font79', CourseResultData.totalGradeValue, 63);

    if(!this.rankingUploded){
      this.img.button4 = game.add.button(190, 100, 'buttonLong',
      this.button4touched, this);
      this.text.lobby = game.add.bitmapText(
      215, 107, 'font57', this.string.postRanking, 7);
    }
  },
  update: function(){

  },


















  button1touched: function(){
    this.retry();
  },
  button2touched: function(){
    this.lobby();
  },
  button3touched: function(){
    this.songSelect();
  },
  button4touched: function(){
    this.postRanking();
  },
  lobby: function() {
    game.state.start('screenLobby');
  },
  songSelect: function() {
    game.state.start('screenCoursePlayInit');
  },
  retry: function(){
    game.state.start('screenPlayInit');
  },
  postRanking: function(){
    game.state.start('screenPostCourseRanking');
  },
};