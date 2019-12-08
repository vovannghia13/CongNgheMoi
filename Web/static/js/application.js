
$(document).ready(function(){
    //connect to the socket server.
    var socket = io.connect('http://' + document.domain + ':' + location.port + '/temperature');
    var numbers_received = [];

    //receive details from server
    socket.on('newdata', function(msg) {
        console.log("Temperature:" + msg.temperature + " - Humidity: " + msg.humidity);          
    });

});