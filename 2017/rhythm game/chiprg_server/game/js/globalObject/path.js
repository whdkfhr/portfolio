var PATH = {
  IMG: 'assets/img/',
  FONT: 'assets/img/fonts/',
  SKIN: 'assets/img/skin/',
  UI: 'assets/img/ui/',

  SOUND: 'assets/sound/',
  BGM: 'assets/sound/BGM/',
  SE: 'assets/sound/SE/',

  STAGE: {
    FREE: 'assets/stage/freeplay/',
    COURSE: 'assets/stage/courseplay/'
  },

  skinName: 'default',
  uiName: 'default',
  stageName: '',
  stageLevel: 0,
  courseName: '',
  entry: 0,

  setStage: function(name, level){
    PATH.stageName = name;
    PATH.stageLevel = level;
  },
  setCourse: function(name){
    PATH.courseName = name;
  },

  skinPath: function(skinName){
    return this.SKIN + skinName + '/';
  },
  uiPath: function(uiName){
    return this.UI + uiName + '/';
  },
  stagePath: function(stageName, stageLevel){
    return this.STAGE.FREE + stageName + '/';
  },
  coursePath: function(courseName){
    return this.STAGE.COURSE + courseName + '/';
  },
  entryPath: function(courseName, entry){
    return this.STAGE.COURSE + courseName + '/entry' + entry + '/';
  }
};