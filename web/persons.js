function sendRequest() {
    var httpRequest;
    if (window.XMLHttpRequest) { //Mozilla, Safari
        httpRequest = new XMLHttpRequest();
    } else if (Window.ActiveXObject) { //IE
        httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
    }
    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload = function () {
        $('#myTable tbody tr').remove();
        var data = JSON.parse(this.response);
        data.forEach(function (item, i, arr) {
            var ratio = (item.completeFactTime / item.completeEstTime).toFixed(2);
            if (isNaN(ratio) || ratio == Infinity) ratio = 0;
            var days=Math.floor(item.workTime/28800);
            var hour=Math.floor((item.workTime % 28800) / 3600);
            var min=Math.floor(((item.workTime % 28800) % 3600) / 60);
            var workTime=days>0?
                days+'d '+ (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min):
                (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min);
            $('#myTable tbody').append('<tr><td>' + item.project + '</td>' +
                '<td><a href=sprints.html?sprint_id='+item.sprintID+'>' + item.sprint + '</a></td>' +
                '<td data-sort-value=\'' + item.workTime + '\' align=\'right\'>' + workTime + '</td>' +
                '<td data-sort-value=\''+item.completeCount+'\'>' + item.completeCount + '</td>' +
                '<td data-sort-value=\'' + item.completeEstTime + '\' align=\'right\'>' + getDateString(item.completeEstTime) + '</td>' +
                '<td data-sort-value=\'' + item.completeFactTime + '\' align=\'right\'>' + getDateString(item.completeFactTime) + '</td>' +
                '<td data-sort-value=\''+ratio+'\'>' + ratio + '</td>' +
                '<td data-sort-value=\''+item.incompleteCount+'\'>' + item.incompleteCount + '</td>' +
                '<td data-sort-value=\'' + item.incompleteEstTime + '\' align=\'right\'>' + getDateString(item.incompleteEstTime) + '</td>' +
                '<td data-sort-value=\'' + item.incompleteFactTime + '\' align=\'right\'>' + getDateString(item.incompleteFactTime) + '</td>' +
                '<td data-sort-value=\'' + item.completeHelpTime + '\' align=\'right\'>' + getDateString(item.completeHelpTime) + '</td>' +
                '<td data-sort-value=\''+item.completeHelpCount+'\'>' + item.completeHelpCount + '</td>' +
                '<td data-sort-value=\'' + item.incompleteHelpTime + '\' align=\'right\'>' + item.incompleteHelpTime + '</td>' +
                '<td data-sort-value=\''+item.incompleteHelpCount+'\'>' + item.incompleteHelpCount + '</td>' +
                '<td data-sort-value=\''+item.codeReturns+'\'>' + item.codeReturns + '</td>' +
                '<td data-sort-value=\''+item.codeDiscussion+'\'>' + item.codeDiscussion + '</td>' +
                '<td data-sort-value=\''+item.codeBranches+'\'>' + item.codeBranches + '</td>' +
                '<td data-sort-value=\''+item.codeMerged+'\'>' + item.codeMerged + '</td>' +
                '<td data-sort-value=\''+item.codeSeen+'\'>' + item.codeSeen + '</td>' +
                '<td data-sort-value=\''+item.codeCommented+'\'>' + item.codeCommented + '</td></tr>');
        });

        function getDateString(sec) {
            var days = Math.floor(sec / 480);
            var hour=Math.floor((sec % 480) / 60);
            var min=Math.floor((sec % 480) % 60);
            return days>0?
                days+'d '+ (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min):
                (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min);
        }

        $('#myTable').footable();
        FooTable.get('#myTable').pageSize(15);
    }
    var select = document.getElementById('selectPerson');
    var arg = select.options.item(select.options.selectedIndex).getAttribute('id');
    httpRequest.open('GET', 'http://localhost:8080/getJobsForPerson/' + arg, true);
    httpRequest.send(null);
};
var id=window.location.search.substring(11);
if(id){
    alert(id);
    var select = document.getElementById('selectPerson');
    //найти элемент с нужным индексом (они были отсортированы, id в базе и индекс в списке не совпадают)
    var index=document.getElementById(id).getAttribute("num");
    select.selectedIndex=Number(index);
    sendRequest();
}