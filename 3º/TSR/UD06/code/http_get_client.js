// http_get_client.js
if (process.argv.length != 3) {
    console.log('usage: node http_get_client port');
    process.exit(0);
}
var http = require('http');
var options = {
    host: 'localhost',
    port: parseInt(process.argv[2]),
    path: '/'
};

function http_client(){ 
    var req = http.get(options, function(response){
        var res_data = '';
        response.on('data', function(chunk){
            res_data += chunk;
        });

        response.on('end', function(){
            console.log(res_data);
        });
    });

    req.on('error', function(e){
        console.log('An error: ' + e.message);
    });
};

for (var i=0; i<10; i++)
    setInterval(http_client, 1);
   