var RGtimer = function(){

  this.start_msec = false;
  this.tempo = 120;
  this.beatSlicer = 0;

  this.current_msec = 0;
  this.current_mbeat = 0;

  // Initialize. bpm decides song tempo for beat per second unit.
  this.init = function(){
    this.start_msec=false;
    this.tempo=120;
    this.beatSlicer=0;
    this.current_msec=0;
    this.current_mbeat=0;
  };

  this.start = function(bpm){
    this.init();
    this.start_msec = Date.now();
    this.current_msec = 0;
    this.current_mbeat = 0;

    // set Tempo
    if((bpm>30) && (bpm<6000)) {
      this.setTempo(bpm);
    }
    // if Invalid BPM: set Tempo = 120 (default)
    else {
      this.setTempo(120);
    }
  };

  this.setTempo = function(bpm){
    this.Tempo = bpm;
    this.beatSlicer = 60/this.Tempo;
  };

  // Get current time for msec unit
  this.getMsec = function(){
    if(this.start_msec === false)
      return 0;
    this.current_msec = Date.now()-this.start_msec;
    return parseInt(this.current_msec);
  };

  // Get current time for beat unit
  this.getMbeat = function(){
    this.current_mbeat = this.current_msec/this.beatSlicer;
    return parseInt(this.current_mbeat);
  };
};