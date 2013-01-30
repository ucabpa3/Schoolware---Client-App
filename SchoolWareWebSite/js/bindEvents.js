function bindEvents(){
    /*============================================
                Sidebar click events
    ==============================================  */
    $("#sidebar nav ul li a").click(function(event){

        event.preventDefault();
        $("#cover").click();

        $("#sidebar nav ul li.selected").removeClass("selected").addClass("non-selected");
        $(this).parent().removeClass("non-selected").addClass("selected");

        if($(this).attr('href') == "#installed-apps"){

            browsingHTML = $("#app-pane").html();

            $("#app-pane").fadeOut("fast",function(){

                var instApps = linker.fetchFile("appList.html");
                if(instApps == "" ||instApps == " "){
                    $("#app-pane").html('<h1 id="start-br">Start browsing applications.</h1>');
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
                $("#app-pane").fadeOut("slow",function(){
                    $(this).html("");
                }).fadeIn("slow");
            }
            else{
                $("#br-cat").animate({left: "-=180"},200);
                $("#app-pane").fadeOut("slow",function(){
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
                $("#app-pane").fadeOut("fast",function(){
                    $(this).html(browsingHTML);
                }).fadeIn("fast");
            }
            else{
                $("#app-pane").html( '<h1 id="start-br">Select a category.</h1>');
                //retrieveAppsByCat(" ");
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

        $("#cover").fadeIn(200);
        $("#cover").append('<div id="full-app-desc"><div id="fad-wrapper"></div></div>');

        var href = $(this).attr("href");
        $(this).parent().clone().appendTo("#fad-wrapper");
        $("#fad-wrapper").append("<p id=\"app-desc\">"+$(this).parent().attr("description")+"</p>");

        $("#full-app-desc div.browse-app img").unwrap();

        if(linker.appExists($("#full-app-desc div.browse-app").text(),$(this).parent().attr("category"))){
                 $("#full-app-desc").append("<div id=\"download\">Installed</div>");
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
            $("#cover").hide();
        });
    });

    $(".install a").live("click",function(event){

        event.preventDefault();

        var classArr = $("#full-app-desc div.browse-app").attr('class').split(" ");
        var cat = classArr[1];
        var url = $(this).attr('href');
        var desc = $("#app-desc").text();

        linker.initiateDownload(url, cat,desc);

        $("#loading-wrapper span").text("Downloading...");
        $("#loading-wrapper").animate({bottom: "+=70"},200);
    });

    $(".installed-app a").live("click",function(event){

        event.preventDefault();

        $("#cover").fadeIn(200);
        $("#cover").append('<div id="full-app-desc"><div id="fad-wrapper"></div></div>');

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

                               updateVar = $("#app-pane").html();
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
        Shared operations
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

  /*  $("#app-pane").scroll(function(){

        if(231 - $(this).scrollTop() == 0) {
              alert("call!");
           }
    });*/
}
