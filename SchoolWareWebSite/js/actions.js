window.onload = function(e){


    var selCategoryIns = "all";
    var sideMenuSel = "ins";
    var selCategoryBr = "all";

    $("#gen-content").html(linker.fetchAppHtml());

    $("#sidebar nav ul li a").click(function(event){

        event.preventDefault();

        $("#sidebar nav ul li.selected").removeClass("selected").addClass("non-selected");
        $(this).parent().removeClass("non-selected").addClass("selected");

        if($(this).attr('href') == "#installed-apps"){

            $("#gen-content").fadeOut("fast",function(){
                 $(this).html(linker.fetchAppHtml());
            }).fadeIn("fast");

            $("#categories li.selected").removeClass("selected");
            $('#'+selCategoryIns).addClass("selected");

            if($("#categories").css("left") == "0px"){
                $("#categories").animate({left: "+=180"},200);
            }

            sideMenuSel = "ins";
        }
        else if($(this).attr('href') == "#_faq_"){
            if($("#categories").css("left") != "0px"){
                $("#categories").animate({left: "-=180"},200);
                $("#gen-content").fadeOut("slow",function(){
                     $(this).html(" ");
                 }).fadeIn("slow");
                }
            sideMenuSel = "faq";
        }
        else{

            $("#categories li.selected").removeClass("selected");
            $('#'+selCategoryBr).addClass("selected");

            if($("#categories").css("left") == "0px"){
                $("#categories").animate({left: "+=180"},200);
            }
            $("#gen-content").fadeOut("fast",function(){
                $(this).html("<a class=" +"downloadble-app"+" href="+"/Users/costas/Documents/UMLet/umlet.jar"+">UMLet</a>"+
                             "<a class=" +"downloadble-app"+" href="+"http://www.scs.stanford.edu/nyu/03sp/notes/l20d.txt"+">120</a>");
            }).fadeIn("fast");

                sideMenuSel = "br";

       }

    });


    $("#categories ul li a").click(function(event){

        event.preventDefault();
        $("#categories li.selected").removeClass("selected");
        $(this).parent().addClass("selected");
        if(sideMenuSel == "ins"){
            selCategoryIns = $("#categories li.selected").attr("id");
        }
        else {selCategoryBr = $("#categories li.selected").attr("id");}

    });

    $(".downloadble-app").live("click", function(){
        event.preventDefault();
        linker.initiateDownload($(this).attr('href'));
        $("#loading-wrapper span").text("Downloading...");
        $("#loading-wrapper").animate({bottom: "+=70"},200);
    });

    $(".installed-app a").live("click",function(){
        var appPath = $(this).attr('href');
        var exit = linker.launchJar(appPath);
        if(exit === 1){
            alert("Failed to launch the application.");
        }
    });

}
