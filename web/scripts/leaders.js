function getLeadersList() {
    var httpRequest;
    if (window.XMLHttpRequest) { //Mozilla, Safari
        httpRequest = new XMLHttpRequest();
    } else if (Window.ActiveXObject) { //IE
        httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
    }
    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload = function () {
        let data = JSON.parse(this.response);
        data.fasterPerson.forEach(function (item, i, arr) {
            $('#fasterPerson').append("<tr><td class='number'>"+(i+1)+"</td><td>" + item.name + "<br/>" + item.id + "<br/>" + item.value + "</td></tr>");
        });

    };
    httpRequest.open('GET', 'http://localhost:8080/getLeadersList', false);
    httpRequest.send(null);
}