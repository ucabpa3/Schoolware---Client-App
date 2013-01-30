/*============================
        Gloabl variables
  ===========================*/

var catHtml = " ";
var instAppsHtml = " ";
var browsingHTML= " ";

/*============================
     Window onload function
  ===========================*/

window.onload = function(e){

    e.preventDefault();

    /*Tweaked jQuery's fx interval for smoother animations in Qt*/
    jQuery.fx.interval = 50;

   // linker.launchJar("/Users/costas/Documents/Coureswork.jar");
    //linker.json();

    /*============================================
            Load html files stored locally
    ==============================================  */
bindEvents();
        instAppsHtml = linker.fetchFile("appList.html");
        if(instAppsHtml !=  ""){
            $("#app-pane").html(instAppsHtml);
        }
        else $("#app-pane").html('<h1 id="start-br">Start browsing applications.</h1>');

        catHtml = linker.fetchFile("cathtml.html");
        if(catHtml != ""){
            $("#inst-cat ul").append(catHtml);
        }
        $('body').fadeIn("fast",function(){

            var msg = linker.bootChecks();
            if(msg){
                //alert("You need the following programs to run applications:\n"+ msg);
                $().toastmessage('showNoticeToast', "You need the following programs to run applications:\n"+ msg);
                //linker.initiateDownload("http://schoolware.cs.ucl.ac.uk:9999/aad-ws/Apps/Default/Coureswork.jar","Math","asdasds");
               // linker.launchJar("/Users/costas/Documents/Coureswork.jar");
            }
            //linker.launchApp("final.jar");
            setTimeout('retrieveCategories();',3000);
        });


}

