function bindEvents(){
    /*============================================
                Sidebar click events
    ==============================================  */
    $("#sidebar nav ul li a").click(function(event){

        event.preventDefault();
        $("#x").click();

        $("#sidebar nav ul li.selected").removeClass("selected").addClass("non-selected");
        $(this).parent().removeClass("non-selected").addClass("selected");

        if($(this).attr('href') == "#installed-apps"){

            browsingHTML = appPane.html();

            appPane.fadeOut("fast",function(){

                var instApps = linker.fetchFile("appList.html");
                if(instApps == "" ||instApps == " "){
                    appPane.html('<h1 id="start-br">Start browsing applications.</h1>');
                }
                else{

                    $(this).html(instApps);
                    var selcat = $("#inst-cat li.selected").text();
                    filterApps(selcat);
                }

            });

            $( "div" ).promise().done(function() {
                $( "#app-pane" ).fadeIn("fast");
              });

            if($("#inst-cat").css("left") != "180px"){
                if($("#br-cat").css("left") != "0px"){
                    $("#br-cat").animate({left: "-=180"},200,function(){
                        $("#inst-cat").animate({left: "+=180"},200);
                    });
                }
                else{
                    $("#inst-cat").animate({left: "+=180"},200);
                }

            }
        }
        else if($(this).attr('href') == "#_faq_"){
            if($("#inst-cat").css("left") != "0px"){
                $("#inst-cat").animate({left: "-=180"},200);
                appPane.fadeOut("slow",function(){
                    $(this).html("");
                }).fadeIn("slow");
            }
            else{
                $("#br-cat").animate({left: "-=180"},200);
                appPane.fadeOut("slow",function(){
                    $(this).html("");
                }).fadeIn("slow");
            }
        }
        else{
            if($("#br-cat").css("left") != "180px"){
                if($("#inst-cat").css("left") != "0px"){
                    $("#inst-cat").animate({left: "-=180"},200,function(){
                        $("#br-cat").animate({left: "+=180"},200);
                    });
                }
                else{
                    $("#br-cat").animate({left: "+=180"},200);
                }

            }
            if(browsingHTML != " "){
                appPane.fadeOut("fast",function(){
                    $(this).html(browsingHTML);
                }).fadeIn("fast");
            }
            else{
                appPane.html( '<h1 id="start-br">Select a category.</h1>');
            }
        }

    });

/*============================================
            Categories click events
============================================== */

    $("#inst-cat ul li a").live("click",function(event){

        event.preventDefault();
        $("#x").click();
        $("#inst-cat li.selected").removeClass("selected");
        $(this).parent().addClass("selected");
        var selcat = $(this).text();
        filterApps(selcat);
    });

    $("#br-cat ul li a").live("click",function(event){

        event.preventDefault();
        $("#x").click();
        $("#br-cat li.selected").removeClass("selected");
        $(this).parent().addClass("selected");
        retrieveAppsByCat($(this).parent().attr("id"));

    });

/*============================================
       Application related events
==============================================*/

    $(".browse-app a").live("click",function(event){

        event.preventDefault();

        cover.fadeIn(200);
        cover.append('<div id="full-app-desc"><div id="fad-wrapper"></div></div>');

        var href = $(this).attr("href");
        $(this).parent().clone().appendTo("#fad-wrapper");
        $("#fad-wrapper").append("<p id=\"app-desc\">"+$(this).parent().attr("description")+"</p>");

        $("#full-app-desc div.browse-app img").unwrap();
        var aname = $("#full-app-desc div.browse-app").text();
        var acat = $(this).parent().attr("category");
       // appExists(aname, acat);
        if(appExists(aname, acat)){
                 $("#full-app-desc").append("<div id=\"download\" class=\"installed\"><a>Installed</a></div>");
        }
        else{
            $("#full-app-desc").append("<div id=\"download\" class=\"install\"><a href=\""+href+"\" onfocus=\"blur();\">Install</a></div>");
        }
        $("#full-app-desc").animate({top: "+=600"},200,function(){
            $("#full-app-desc").prepend('<div id="x"><a>CLOSE<img src="img/x.png"/></a></div>');
        });
    });

    $("#x").live("click",function(){
        $("#full-app-desc").animate({top: "-=600"},200,function(){
            $(this).remove();
            cover.hide();
        });
    });

    $(".install a").live("click",function(event){

        event.preventDefault();

        var classArr = $("#full-app-desc div.browse-app").attr('class');
        var cat = $("#full-app-desc div.browse-app").attr('category');
        var url = $(this).attr('href');
        var desc = $("#app-desc").text();
        var app_name = $("#full-app-desc div.browse-app").text();

        linker.initiateDownload(url, app_name, cat, desc);

        loadingText.text("Downloading...");
        loading.animate({bottom: "+=70"},200);
    });

    $(".installed-app a").live("click",function(event){

        event.preventDefault();

        cover.fadeIn(200);
        cover.append('<div id="full-app-desc"><div id="fad-wrapper"></div></div>');

        var href = $(this).attr("href");
        var AppName = $(this).text();
        $(this).parent().clone().appendTo("#fad-wrapper");
        $("#fad-wrapper").append("<p id=\"app-desc\">"+$(this).parent().attr("description")+"</p>");

        $("#full-app-desc div.installed-app img").unwrap();
        $("#full-app-desc").append("<div id=\"launch\"><a href=\""+href+"\" onfocus=\"blur();\">Launch</a></div>");
        $("#full-app-desc").append("<div id=\"download\" class=\"uninstall\" category=\""+$(this).parent().attr("category")+"\"><a class href=\""+AppName +"\" onfocus=\"blur();\">Uninstall</a></div>");

        $("#full-app-desc").animate({top: "+=600"},200,function(){
            $("#full-app-desc").prepend('<div id="x"><a>CLOSE<img src="img/x.png"/></a></div>');
        });
    });

    $("#launch a").live("click",function(){
        var appPath = $(this).attr('href');

            var exit = linker.launchApp(appPath);
            if(exit === 1){
                $().toastmessage('showErrorToast', "Failed to launch the application.");
            }
    });

    $(".uninstall a").live("click",function(){

        var appname = $(this).attr("href");
        var category = $(this).parent().attr("category");

        if(linker.uninstallApp(appname, category)){

            var count = 0;

            $("#app-pane div").each(function(){

                if($(this).attr('category') == category && $(this).find("a").text() == appname){

                    var elemToRemove = $(this);

                    $("#x").click();
                    $("#x").promise().done(function(){

                        elemToRemove.fadeOut("slow",function(){

                            $(this).remove();
                            var updateVar = "";
                            if($("#app-pane div").length > 0){

                               updateVar = appPane.html();
                            }
                            linker.updateFile("appList.html",updateVar);

                        });
                    });

                }
                else if($(this).attr('category') == category){
                    count ++;
                }
                if (count == 0 ){

                    $("#inst-cat  #"+category).remove();
                    var updateData = "";
                    if($("#inst-cat ul li").length != 1){
                        updateData = $("#inst-cat ul").html();
                    }

                    linker.updateFile("cathtml.Html",updateData);
                }
            });
        }
        else $().toastmessage('showErrorToast', "Something went wrong!");
    });


   /*============================
        Useful operations
     ===========================*/

    /* Function used to filter installed apps based on their category*/

    function filterApps(selcat){

        if(selcat == "All"){
            $("#app-pane div").each(function(){
                if($(this).is(":hidden")){
                    $(this).show("fast");
                }
            });
        }
        else{
            $("#app-pane div").each(function(){

             var str = $(this).attr("category");
                if(selcat != str){
                    $(this).hide("slow");
                }
                 else{
                    $(this).show("slow");
                }
            });
         }
    }

    /* Check if application exists */

    function appExists(appname, category){

        var apps = linker.fetchFile("update.json");

        if(apps != " "){
        try{
            var obj = JSON.parse(apps);
            for (var i = 0, len = obj.length; i < len; i++) {
                if(obj[i].Appname == appname && obj[i].Category === category){
                    return true;
                }
            }
        }catch(e){
            $().toastmessage('showErrorToast', "Error: Applications file corrupted");
        }
        }
        return false;
    }
  /*  appPane.scroll(function(){

        if(231 - $(this).scrollTop() == 0) {
              alert("call!");
           }
    });*/
}
