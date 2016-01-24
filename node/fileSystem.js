var fs = require("fs");

var filesSync = fs.readdirSync(".");
console.log(filesSync);

var files = fs.readdir(".", function(err, stdout) {
  if (err) { throw err; }
  console.log(`Files: ${stdout}`)
});

console.log("reading files");

