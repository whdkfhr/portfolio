var screenPostCourseRanking = {
  name: "screenPostCourseRanking",
  uiPath: "",
  var: "",
  strings: {
    title: "POST RANKING",
    name: "NAME: ",
    postbutton: "POST"
  },
  text: {},
  vkey: "",
  preload: function(){
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
  },
  create: function(){
    this.var = CourseResultData;
    this.text.screenTitle = game.add.bitmapText(
      10, 11, 'font79', this.strings.title, 9);
    this.text.courseTitle = game.add.bitmapText(
      20, 37, 'font57', 'LV.'+ SomeMath.pad0(this.var.courseLevel, 2, ' ') +
      ' ' + this.var.courseTitle, 7);
    this.text.totalScore = game.add.bitmapText(
      185, 37, 'font57', 'TOTAL SCORE: '+SomeMath.pad0(this.var.totalScore, 8, 0), 7);
    
    this.text.name = game.add.bitmapText(
      20, 50, 'font79', this.strings.name, 9);

    this.vkey = new Vkeyboard(10, 90);
    this.vkey.pressEnter = function(){
      if(screenPostCourseRanking.vkey.isOn){
        screenPostCourseRanking.vkey.keyboardToggle('OFF');
        screenPostCourseRanking.vkey.dialog('ON', 'POST RANKING DATA WITH THIS NAME?')
      }
    }
    this.vkey.pressOk = function(){
      screenPostCourseRanking.updateRanking();
      screenPostCourseRanking.goResult();
    }
  },
  update: function(){
    if(this.vkey.isOn){
      this.vkey.beaming();
      this.vkey.padInput();
      this.vkey.keyInput();
      this.strings.name = ('NAME: ' + this.vkey.string);
      this.text.name.setText(this.strings.name);
    }
    else{
      this.vkey.moveDialogSelector();
      this.vkey.pressDialogButton();
    }
  },

  updateRanking: function(){
    var query = new RGquery;
    query.postCourseRanking(this.vkey.string, 'guest', this.var.courseID, this.var.totalScore);
  },

  goResult: function(){
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    screenCourseResult.rankingUploded = true;
    game.state.start('screenCourseResult');
  }
};