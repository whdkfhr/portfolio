var CourseResultData = {
  courseID: "",
  courseTitle: "",
  courseLevel: "",
  entry: [
    {
      title: "",
      score: 0,
      gradeRate: 0,
      gradeValue: "",
      isAll: "",
    },
    {
      title: "",
      score: 0,
      gradeRate: 0,
      gradeValue: "",
      isAll: "",
    },
    {
      title: "",
      score: 0,
      gradeRate: 0,
      gradeValue: "",
      isAll: "",
    },
    {
      title: "",
      score: 0,
      gradeRate: 0,
      gradeValue: "",
      isAll: "",
    },
  ],
  totalScore: 0,
  totalGradeRate: 0,
  totalGradeValue: "",
  calcTotal: function(){
    for(var i=0; i<4; i++){
      this.totalScore += this.entry[i].score;
      this.totalGradeRate += this.entry[i].gradeRate/4;
      if(this.totalGradeRate>=98)      this.totalGradeValue = 'SS';
      else if(this.totalGradeRate>=95) this.totalGradeValue = 'S';
      else if(this.totalGradeRate>=90) this.totalGradeValue = 'A';
      else if(this.totalGradeRate>=80) this.totalGradeValue = 'B';
      else if(this.totalGradeRate>=70) this.totalGradeValue = 'C';
      else if(this.totalGradeRate>=50) this.totalGradeValue = 'D';
      else                             this.totalGradeValue = 'F';
    }
  }
};