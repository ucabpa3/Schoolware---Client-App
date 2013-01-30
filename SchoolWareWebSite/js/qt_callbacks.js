function finishedDownload(msg){
    $("#loading-wrapper").animate({bottom: "-=70" },200,function(){

        if(msg){
            $().toastmessage('showErrorToast', msg);
        }
        else{
            //var asd = linker.fetchFile("cathtml.html");
            $("#inst-cat ul").append(linker.fetchFile("cathtml.html"));
            $(".install a").fadeOut("fast",function(){
                $(this).replaceWith("<a>Installed</a>");
            }).fadeIn("fast");
        }
    });

}

function installing(){
       $("#loading-wrapper span").text("Sending resutls...");
}
