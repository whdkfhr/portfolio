var screenCourseInit = {
  courseData: "",
  var: {
    isCoursePlay: false,
    currentEntry: 0
  },
  preload: function(){
    game.load.json(
      'courseData',
      PATH.coursePath(PATH.courseName)+'courseData.json');
  },
  create: function(){
    courseData = game.cache.getJSON('courseData');
    CourseResultData.courseID = courseData.courseID;
    CourseResultData.courseTitle = courseData.title;
    CourseResultData.courseLevel = courseData.level;
    for(var i=0; i<4; i++){
      CourseResultData.entry[i].title = courseData.entry[i].title;
    }
  },
  update: function(){
    this.var.isCoursePlay = true;
    console.log('isCourse ' + this.var.isCoursePlay);
    if(this.var.currentEntry >= 4){
      console.log('go screenCourseResult');
      this.var.isCoursePlay = false;
      this.var.currentEntry = 0;
      screenCourseResult.rankingUploded = false;
      game.state.start('screenCourseResult');
    }
    else{
      console.log('go screenPlayEntryInit');
      game.state.start('screenPlayEntryInit');
    }
  }

};
