window.onload = function(e){

    e.preventDefault();
    /*Tweaked jQuery's fx interval for smoother animations in Qt*/
    jQuery.fx.interval = 50;

    var sideMenuSel = "ins";

   // var str = linker.fetchFile("update.json");
    //var json = eval("(" + str + ")");
    //alert(json);

    // $(jQuery.parseJSON(JSON.stringify(json))).each(function() {
    //   alert(this.Appid);
    //});
   // linker.launchJar("/Users/costas/Documents/Coureswork.jar");
    //alert(json);

    /*============================================
            Load html files stored locally
    ==============================================  */
    var content = linker.fetchFile("appList.html");
    if(content != ' '){
        $("#app-pane").html(content);
    }
    else $("#app-pane").html('<h1 id="start-br">Start browsing applications.</h1>');

    var cats = linker.fetchFile("cathtml.html");
    if(cats != " "){
        $("#inst-cat ul").html(cats);
    }

    /*============================================
                Sidebar click events
    ==============================================  */

    $("#sidebar nav ul li a").click(function(event){

        event.preventDefault();
        $("#cover").click();

        $("#sidebar nav ul li.selected").removeClass("selected").addClass("non-selected");
        $(this).parent().removeClass("non-selected").addClass("selected");

        if($(this).attr('href') == "#installed-apps"){

            $("#app-pane").fadeOut("fast",function(){
                $(this).html(linker.fetchFile("appList.html"));
                var selcat = $("#inst-cat li.selected").text();
                filterApps(selcat);
                $( "div" ).promise().done(function() {
                    $( "#app-pane" ).fadeIn("fast");
                  });
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
            sideMenuSel = "ins";
        }
        else if($(this).attr('href') == "#_faq_"){
            if($("#inst-cat").css("left") != "0px"){
                $("#inst-cat").animate({left: "-=180"},200);
                $("#app-pane").fadeOut("slow",function(){
                    $(this).html(" ");
                }).fadeIn("slow");
            }
            else{
                $("#br-cat").animate({left: "-=180"},200);
                $("#app-pane").fadeOut("slow",function(){
                    $(this).html(" ");
                }).fadeIn("slow");
            }
            sideMenuSel = "faq";
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
            var dataArray = [ { "categoryName" : "Accounting",
                                 "description" : "test",
                                 "name" : "GC01-Accounting.jar",
                                 "size" : "test1",
                                 "url" : "http://subtlepatterns.subtlepatterns.netdna-cdn.com/patterns/asfalt.zip"
                             },
                             { "categoryName" : "DigitalLogic",
                                 "description" : "test",
                                 "name" : "GC01DIGITALLOGIC.jar",
                                 "size" : "test1",
                                 "url" : "http://fs10n3.sendspace.com/dl/44dbfca7541db5df396a93bd2e4c117e/5101b60a0d778792/32oxon/ps3tools.zip"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "Coureswork.jar",
                                 "size" : "test1",
                                 "url" : "http://www.dashhacks.com/downloads/finish/5-ps3-downloads/8761-showtime-test-build/0.html"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Cat1",
                                 "description" : "lorem ipsum posum akjdg asslkfjdlk slkdjf lksdjf dkfj lskdfjkl sdfjkdjfkdklfjsdklfj kjfksdljfdlskfjdskfjsdlk jsdkfjsdjfjfkjkdf  lkdjfkl jsdk jkjk fjsdlkfj kljfjkd akjsd kjasgdk jagsdgaksdg asjkgd jasgdj gaskgd asgdjg askjdg jkasgdjsagdjksag djksg jsdgjk gdkjg sadg jasgdjgkjasgd gasjd gaskjgdjaskdgjkasgdjsgdjkasgd",
                                 "name" : "umlet.jar",
                                 "size" : "test1",
                                 "url" : "/Users/costas/Documents/UMLet/umlet.jar"
                             },
                             { "categoryName" : "Cat2",
                                 "description" : "ajsgdajgd ajhdgahsgdasdg sd gshdg jagdhgdasg gsdjgashg hag jagaj",
                                 "name" : "120d.txt",
                                 "size" : "test1",
                                 "url" : "http://www.scs.stanford.edu/nyu/03sp/notes/l20d.txt"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             },
                             { "categoryName" : "Maths",
                                 "description" : "test",
                                 "name" : "quiz_gui.exe",
                                 "size" : "test1",
                                 "url" : "C:\\Users\\MConstantinides\\git\\aad-webservice\\Apps\\Maths\\quiz_gui.exe"
                             }
                    ];

            $("#app-pane").fadeOut("fast",function(){
                $(this).empty();
                $(jQuery.parseJSON(JSON.stringify(dataArray))).each(function() {
                     $("#app-pane").append('<div class="browse-app '+this.categoryName+'" description=\"'+this.description+'\"><a href="'+this.url+'"><img src="img/application_icon.png" onfocus="blur();"/>'+this.name+'</a></div>');
                     $(".browse-app").fadeIn("fast");
                 });
            }).fadeIn("fast");


            // $("#app-pane").fadeOut("fast",function(){
              //   $(this).html('<a class="browse-app Cat1" description="lalal" href="/Users/costas/Documents/UMLet/umlet.jar">UMLet</a><a class="browse-app Cat2" href="http://www.scs.stanford.edu/nyu/03sp/notes/l20d.txt">120</a>');
            //}).fadeIn("fast");

            sideMenuSel = "br";

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

    $("#br-cat ul li a").click(function(event){

        event.preventDefault();
        $("#x").click();
        $("#br-cat li.selected").removeClass("selected");
        $(this).parent().addClass("selected");

    });

/*============================================
       Application related events
==============================================  */

    $(".browse-app a").live("click",function(event){

        event.preventDefault();

        $("#cover").fadeIn(200);
        $("#cover").append('<div id="full-app-desc"><div id="fad-wrapper"></div></div>');

        var href = $(this).attr("href");
        $(this).parent().clone().appendTo("#fad-wrapper");
        $("#fad-wrapper").append("<p id=\"app-desc\">"+$(this).parent().attr("description")+"</p>");

        $("#full-app-desc div.browse-app img").unwrap();
        if(linker.appExists($("#full-app-desc div.browse-app").text())){
                 $("#full-app-desc").append("<div id=\"download\"><p>Installed</p></div>");
        }
        else{
            $("#full-app-desc").append("<div id=\"download\" class=\"install\"><p><a href=\""+href+"\" onfocus=\"blur();\">Install</a></p></div>");
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

    $(".install p a").live("click",function(event){

        event.preventDefault();

        var classArr = $("#full-app-desc div.browse-app").attr('class').split(" ");
        var cat = classArr[1];
        var url = $(this).attr('href');
        linker.initiateDownload(url, cat);
        $("#loading-wrapper span").text("Downloading...");
        $("#loading-wrapper").animate({bottom: "+=70"},200,function(){
            $(".install p").fadeOut("fast",function(){
                $(this).replaceWith("<p>Installed</p>");
            }).fadeIn("fast");
        });
    });

    $(".installed-app a").live("click",function(){
        var appPath = $(this).attr('href');
        var exit = linker.launchJar(appPath);
        if(exit === 1){
            alert("Failed to launch the application.");
        }
    });

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
             var str = $(this).attr("class");
             var strlist = str.split(" ");
                if(selcat != strlist[1]){
                    $(this).hide("slow");
                }
                 else{
                    $(this).show("slow");
                }
            });
         }
    }
}
