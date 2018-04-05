var C2Trackers = {
  bgmLoop:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(-1)), bf: "", path:""},
  bgmNonLoop:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(0)), bf: "", path:""},
  se1:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(0)), bf: "", path:""},
  se2:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(0)), bf: "", path:""},
  se3:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(0)), bf: "", path:""},
  se4:
    {tk: new ChiptuneJsPlayer(new ChiptuneJsConfig(0)), bf: "", path:""},
};

var C2TrackerControl = {
  load: function(tracker, path){
    tracker.path = path;
    tracker.tk.load(path, function(buf) {
      tracker.bf = buf;
    });
  },
  play: function(tracker){
    tracker.tk.load('', function() {
      tracker.tk.play(tracker.bf);
    });
  },
  songStart: function(tracker){
    tracker.tk.load('', function() {
      tracker.tk.play(tracker.bf);
    });
  },
  stop: function(tracker){
    tracker.tk.load('', function() {
      tracker.tk.stop();
    });
  },
};
