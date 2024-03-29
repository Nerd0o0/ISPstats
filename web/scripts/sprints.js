function getSprints(){
    var httpRequest;
    if(window.XMLHttpRequest){ //Mozilla, Safari
        httpRequest=new XMLHttpRequest();
    } else if(Window.ActiveXObject){ //IE
        httpRequest=new ActiveXObject('Microsoft.XMLHTTP');
    }

    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload=function() {
        $('#selectSprint option').remove();
        var sprints=JSON.parse(this.response);
        var a=0;
        sprints.forEach(function(item,i,arr){
            $('#selectSprint').append('<option id=sprint_'+item.sprintID+' num='+a+'>'+item.name+'</option>');
            a++;
        });
    };
    var select=document.getElementById('selectProject');
    var arg = select.options.item(select.options.selectedIndex).getAttribute('id').substr(8 );
    httpRequest.open('GET', 'http://127.0.0.1:8080/getSprintsForProject/'+arg, false);
    httpRequest.send(null);
}

function getProjects(){
    var httpRequest;
    if(window.XMLHttpRequest){ //Mozilla, Safari
        httpRequest=new XMLHttpRequest();
    } else if(Window.ActiveXObject){ //IE
        httpRequest=new ActiveXObject('Microsoft.XMLHTTP');
    }
    httpRequest.overrideMimeType('text/ajax');
    httpRequest.onload=function() {
        $('#selectProject option').remove();
        var sprints=JSON.parse(this.response);
        var a=0;
        sprints.forEach(function(item,i,arr){
            $('#selectProject').append('<option id=\'project_'+item.projectID+'\' num='+a+'>'+item.name+'</option>');
            a++;
        });
    }
    httpRequest.open('GET', 'http://localhost:8080/getProjects', false);
    httpRequest.send(null);
}

function sendRequest(){
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
            var ratio=(item.completeFactTime/item.completeEstTime).toFixed(2);
            if(isNaN(ratio) || ratio==Infinity) ratio=0;
            var days=Math.floor(item.workTime/28800);
            var hour=Math.floor((item.workTime % 28800) / 3600);
            var min=Math.floor(((item.workTime % 28800) % 3600) / 60);
            var workTime=days>0?
                days+'d '+ (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min):
                (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min);
            $('#myTable tbody').append('<tr><td><a href=\'persons.html?person_id='+item.personID+'\'>'+item.person+'</a></td>' +
                '<td data-sort-value=\''+item.workTime+'\' align=\'right\'>'+ workTime +'</td>' +
                '<td data-sort-value=\''+item.completeCount+'\'>'+item.completeCount+'</td>' +
                '<td data-sort-value=\''+item.completeEstTime+'\' align=\'right\'>'+getDateString(item.completeEstTime)+'</td>' +
                '<td data-sort-value=\''+item.completeFactTime+'\' align=\'right\'>'+getDateString(item.completeFactTime)+'</td>' +
                '<td data-sort-value=\''+ratio+'\'>'+ratio+'</td>' +
                '<td data-sort-value=\''+item.incompleteCount+'\'>'+item.incompleteCount+'</td>' +
                '<td data-sort-value=\''+item.incompleteEstTime+'\' align=\'right\'>'+getDateString(item.incompleteEstTime)+'</td>' +
                '<td data-sort-value=\''+item.incompleteFactTime+'\' align=\'right\'>'+getDateString(item.incompleteFactTime)+'</td>' +
                '<td data-sort-value=\''+item.completeHelpTime+'\' align=\'right\'>'+getDateString(item.completeHelpTime)+'</td>' +
                '<td data-sort-value=\''+item.completeHelpCount+'\'>'+item.completeHelpCount+'</td>' +
                '<td data-sort-value=\''+item.incompleteHelpTime+'\' align=\'right\'>'+getDateString(item.incompleteHelpTime)+'</td>' +
                '<td data-sort-value=\''+item.incompleteHelpCount+'\'>'+item.incompleteHelpCount+'</td>' +
                '<td data-sort-value=\''+item.codeReturns+'\'>'+item.codeReturns+'</td>' +
                '<td data-sort-value=\''+item.codeDiscussion+'\'>'+item.codeDiscussion+'</td>' +
                '<td data-sort-value=\''+item.codeBranches+'\'>'+item.codeBranches+'</td>' +
                '<td data-sort-value=\''+item.codeMerged+'\'>'+item.codeMerged+'</td>' +
                '<td data-sort-value=\''+item.codeSeen+'\'>'+item.codeSeen+'</td>' +
                '<td data-sort-value=\''+item.codeCommented+'\'>'+item.codeCommented+'</td></tr>');
        });
        function getDateString(sec){
            var days=Math.floor(sec/480);
            var hour=Math.floor((sec % 480) / 60);
            var min=Math.floor((sec % 480) % 60);
            return days>0?
                days+'d '+ (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min):
                (hour<10?('0'+hour):hour) + ':' + (min<10?('0'+min):min);
        }
        function getInfoForPerson(id){
            location.href='persons.jsp';
            $('#selectPerson').items.setSelected(id);
        }
        $('#myTable').footable();
        FooTable.get('#myTable').pageSize(15);
    }
    var select=document.getElementById('selectSprint');
    var arg = select.options.item(select.options.selectedIndex).getAttribute('id').substr(7);
    httpRequest.open('GET', 'http://localhost:8080/getJobsForSprint/'+arg, false);
    httpRequest.send(null);
}

//это код для перехода из других таблиц по жмакабельным названиям спринта
function openFromLink() {
    var id = window.location.search.substring(11);

    if (id) {
        var httpRequest;
        if (window.XMLHttpRequest) { //Mozilla, Safari
            httpRequest = new XMLHttpRequest();
        } else if (Window.ActiveXObject) { //IE
            httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
        }
        httpRequest.overrideMimeType('text/ajax');
        httpRequest.onload = function () {
            //переключить на проект
            var data = JSON.parse(this.response);
            var select = document.getElementById('selectProject');
            //найти элемент с нужным индексом (они были отсортированы, id в базе и индекс в списке не совпадают)
            var index = document.getElementById('project_' + data[0].projectID).getAttribute("num");
            select.selectedIndex = Number(index);
            getSprints(false);

            //переключить на спринт
            var select = document.getElementById('selectSprint');
            //найти элемент с нужным индексом (они были отсортированы, id в базе и индекс в списке не совпадают)
            var index = document.getElementById('sprint_'+id).getAttribute('num');
            select.selectedIndex = Number(index);
            //вывод информации о спринте
            sendRequest();
        }
        httpRequest.open('GET', 'http://127.0.0.1:8080/getProjectForSprint/' + id, true);
        httpRequest.send(null);
    }
}