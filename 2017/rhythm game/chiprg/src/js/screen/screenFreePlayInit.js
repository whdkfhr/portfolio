var screenFreePlayInit = {
  allPlaylist: "",
  preload: function(){
    // Load Playlist
    game.load.json('allPlaylist', PATH.STAGE.FREE+'list.json');
  },
  create: function(){
    this.allPlaylist = game.cache.getJSON('allPlaylist');
  },
  update: function(){
    this.state.start('screenFreePlay');
  }
};