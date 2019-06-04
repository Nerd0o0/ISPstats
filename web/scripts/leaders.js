function getLeadersList() {
    var httpRequest;
    if (window.XMLHttpRequest) { //Mozilla, Safari
        httpRequest = new XMLHttpRequest();
    } else if (Window.ActiveXObject) { //IE
        httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
    }
    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload = function () {
        var data = JSON.parse(this.response);
        data.fasterPerson.forEach(function (item, i, arr) {
            console.log(item);
            $('#fasterPerson').append("<p>" + item.name + "<br/>" + item.personID + "<br/>" + item.value + "</p>");
        });

    };
    httpRequest.open('GET', 'http://localhost:8080/getLeadersList', false);
    httpRequest.send(null);
}