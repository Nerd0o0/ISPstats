function send() {
    let obj=document.getElementById('file');
    let str="";
    let fileReader=new FileReader();
    fileReader.readAsText(obj.files[0]);
    fileReader.onload=(function(file,data){
        var httpRequest;
        if(window.XMLHttpRequest){ //Mozilla, Safari
            httpRequest=new XMLHttpRequest();
        } else if(Window.ActiveXObject){ //IE
            httpRequest=new ActiveXObject('Microsoft.XMLHTTP');
        }
        httpRequest.overrideMimeType('text/ajax');
        httpRequest.onload=function() {alert("Успешно");};
        httpRequest.open('POST', 'http://localhost:8080/update-database', false);
        httpRequest.send(fileReader.result);
    });

}