var exec = require('child_process').exec;

//exec("open http://linkedin.com");
exec("ls", function(err, stdout){
  if (err) {
    throw err;
  }

  console.log("listing finished");
  console.log(stdout);
});
