function finishedDownload(msg){
    $("#loading-wrapper").animate({bottom: "-=70" },200,function(){
        $("#inst-cat ul").html(linker.fetchFile("cathtml.html"));
        if(msg != ' '){
            alert(msg);
        }
    });

}

function jsonCallback(dataArray){

}
