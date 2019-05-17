document.onload=jQuery(function($){
    var httpRequest;
    if(window.XMLHttpRequest){ //Mozilla, Safari
        httpRequest=new XMLHttpRequest();
    } else if(Window.ActiveXObject){ //IE
        httpRequest=new ActiveXObject('Microsoft.XMLHTTP');
    }
    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload=function() {
        $('#myTable tbody tr').remove();
        var data=JSON.parse(this.response);
        data.forEach(function(item,i,arr){
            var ratio=(item.completeBugFact/item.completeBugEstimation).toFixed(2);
            if(isNaN(ratio) || ratio==Infinity) ratio=0;
            $('#myTable tbody').append('<tr>' +
                '<td data-sort-value=\''+item.begin+'\'>'+item.project+'</td>' +
                '<td data-sort-value=\''+item.begin+'\'><a href=\'sprints.html?sprint_id='+item.sprintID+'\'>'+item.sprint+'</a></td>' +
                '<td data-sort-value=\''+item.bugCount+'\'>'+ item.bugCount +'</td>' +
                '<td data-sort-value=\''+item.estimationBugTime+'\' align=\'right\'>'+getDateString(item.estimationBugTime)+'</td>' +
                '<td data-sort-value=\''+item.completeBugCount+'\'>'+ item.completeBugCount +'</td>' +
                '<td data-sort-value=\''+item.completeBugEstimation+'\' align=\'right\'>'+getDateString(item.completeBugEstimation)+'</td>' +
                '<td data-sort-value=\''+item.completeBugFact+'\' align=\'right\'>'+getDateString(item.completeBugFact)+'</td>' +
                '<td data-sort-value=\''+ratio+'\'>'+ratio+'</td>' +
                '<td data-sort-value=\''+item.incompleteBugCount+'\'>'+item.incompleteBugCount+'</td>' +
                '<td data-sort-value=\''+item.incompleteBugEstimation+'\' align=\'right\'>'+getDateString(item.incompleteBugEstimation)+'</td>' +
                '<td data-sort-value=\''+item.incompleteBugFact+'\' align=\'right\'>'+getDateString(item.incompleteBugFact)+'</td>' +
                '<td data-sort-value=\''+item.codeReturns+'\'>'+item.codeReturns+'</td>' +
                '<td data-sort-value=\''+item.codeDiscussion+'\'>'+item.codeDiscussion+'</td></tr>');
        });
        function getDateString(sec){
            var days=Math.floor(sec/480);
            var hour=Math.floor((sec % 480) / 60);
            var min=Math.floor((sec % 480) % 60);
            return days>0?
                days+'d '+ (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min):
                (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min);
        }
        $('#myTable').footable();
        FooTable.get('#myTable').pageSize(15);88
    }
    httpRequest.open('GET', 'http://localhost:8080/getSprintsAndProjects', true);
    httpRequest.send(null);
});