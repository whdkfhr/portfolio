var screenRankingInit = {
  freePlayList: "",
  coursePlayList: "",
  preload: function(){
    // Load Playlist
    game.load.json('freePlaylist', PATH.STAGE.FREE+'list.json');
    game.load.json('coursePlaylist', PATH.STAGE.COURSE+'list.json');
  },
  create: function(){
    this.freePlaylist = game.cache.getJSON('freePlaylist');
    this.coursePlaylist = game.cache.getJSON('coursePlaylist');
  },
  update: function(){
    this.state.start('screenRanking');
  }
};