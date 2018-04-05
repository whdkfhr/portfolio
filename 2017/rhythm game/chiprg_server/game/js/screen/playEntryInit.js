var screenPlayEntryInit = {
  skindata: "",
  stagedata: "",
  loadimg: "",
  loadTimer: new RGtimer(),
  preload: function(){

    // for only showcase build
    /*
    PATH.stageName = '16cp2';
    PATH.stageLevel = '1';
    */

    // Load Song Data
    game.load.spritesheet(
      'loadimg',
      PATH.coursePath(PATH.courseName)+'loadimg.png', 320, 180);
    game.load.json(
      'stagedata',
      PATH.entryPath(PATH.courseName, screenCourseInit.var.currentEntry)+'entryData.json');

    // Load Skin
    game.load.json(
      'skindata',
      PATH.skinPath(PATH.skinName)+'skindata.json');
  },
  create: function(){
    this.loadTimer.start(120);
    this.loadimg = game.add.sprite(0, 0, 'loadimg', screenCourseInit.var.currentEntry);
    Skindata = game.cache.getJSON('skindata');
    Stagedata = game.cache.getJSON('stagedata');
    C2TrackerControl.load(C2Trackers.bgmNonLoop, 
      PATH.entryPath(PATH.courseName, screenCourseInit.var.currentEntry) + 'bgm.xm');
  },
  update: function(){
    if(this.loadTimer.getMsec()>=2000) {
      game.state.start('screenPlay');
    }
  }

};
