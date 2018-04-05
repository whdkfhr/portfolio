var screenCoursePlayInit = {
  allCourseList: "",
  preload: function(){
    // Load Playlist
    game.load.json(
      'allCourseList', PATH.STAGE.COURSE+'list.json');
  },
  create: function(){
    this.allCourseList = game.cache.getJSON('allCourseList');
  },
  update: function(){
    game.state.start('screenCoursePlay');
  }
};