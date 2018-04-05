var Query = {};
var MongoClient = require('mongodb').MongoClient;
var Db = require('mongodb').Db;
var Server = require('mongodb').Server;

// [CONNECTION]
Query.connectDB = function(dbPath){
  return new Promise(function(resolve, reject){
    MongoClient.connect(dbPath, function(err, res){
      if(err) throw err;
      resolve(res);
    });
  });
};

// [COLLECTION USER]
Query.getUser = function(db, _userID){
  return new Promise(function(resolve, reject){
    var findMethod = function(){
      if(_userID == undefined){
        return {};
      }      
      return {userID: _userID};
    };
    var sortMethod = function(){
      return {userID: 1};
    };
    db.collection("userdata")
      .find(findMethod())
      .sort(sortMethod())
      .toArray(function(err, res){
        if(err) throw err;
        resolve(res);
        db.close();
      });
  });
};


// [COLLECTION freeranking]
Query.getFreeRanking = function(db, _stageID, _userID, _limit){
  return new Promise(function(resolve, reject){
    var findMethod = function(){
      if(_stageID == undefined && _userID == undefined){
        return {};
      }
      if(_stageID == undefined){
        return {userID: _userID};
      }
      if(_userID == undefined){
        return {stageID: _stageID};
      }      
      return {userID: _userID, stageID: _stageID};
    };

    var sortMethod = function(){
      return {score:-1, date:1};
    };

    if(_limit == undefined){
      db.collection("freeranking")
        .find(findMethod())
        .sort(sortMethod())
        .toArray(function(err, res){
          if(err) throw err;
          resolve(res);
          db.close();
        });
    }
    else{
      db.collection("freeranking")
        .find(findMethod())
        .sort(sortMethod())
        .limit(parseInt(_limit))
        .toArray(function(err, res){
          if(err) throw err;
          resolve(res);
          db.close();
        });
    }
  });
};

Query.postFreeRanking = function(db, body){
  return new Promise(function(resolve, reject){
    var date = new Date();
    var object = {
      userID: body.userID,
      userType: body.userType,
      stageID: body.stageID,
      score: body.score,
      date: date.getTime()
    };
    console.log(object);
    db.collection("freeranking")
      .insert(object, function(err, res){
      if(err) throw err;
        resolve(res);
        db.close();
      });
  });
};



// [COLLECTION courseranking]
Query.getCourseRanking = function(db, _courseID, _userID, _limit){
  return new Promise(function(resolve, reject){
    var findMethod = function(){
      if(_courseID == undefined && _userID == undefined){
        return {};
      }
      if(_courseID == undefined){
        return {userID: _userID};
      }
      if(_userID == undefined){
        return {courseID: _courseID};
      }      
      return {userID: _userID, courseID: _courseID};
    };

    var sortMethod = function(){
      return {score:-1, date:1};
    };

    if(_limit == undefined){
      db.collection("courseranking")
        .find(findMethod())
        .sort(sortMethod())
        .toArray(function(err, res){
          if(err) throw err;
          resolve(res);
          db.close();
        });
    }
    else{
      db.collection("courseranking")
        .find(findMethod())
        .sort(sortMethod())
        .limit(parseInt(_limit))
        .toArray(function(err, res){
          if(err) throw err;
          resolve(res);
          db.close();
        });
    }
  });
};

Query.postCourseRanking = function(db, body){
  return new Promise(function(resolve, reject){
    var date = new Date();
    var object = {
      userID: body.userID,
      userType: body.userType,
      courseID: body.courseID,
      score: body.score,
      date: date.getTime()
    };
    console.log(object);
    db.collection("courseranking")
      .insert(object, function(err, res){
      if(err) throw err;
        resolve(res);
        db.close();
      });
  });
};

// [COLLECTION stagedata]

// [COLLECTION coursedata]

module.exports = Query;