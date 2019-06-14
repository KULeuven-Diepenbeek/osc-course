function altToCaption() {

    var display_str = 1;

    $("img").each(function() {
        var imageCaption = $(this).attr("alt");
        if (imageCaption != '') {
            var imgWidth = $(this).width();
            var imgHeight = $(this).height();
            var position = $(this).position();
            var positionTop = (position.top + imgHeight - 26);
            $("<div clas=''>Figure " + display_str++ + ": " + imageCaption + "</div>").insertAfter(this);

            /*css({
              
            /*$("<span class='img-caption'><em>Figure " + display_str++ + ": " + imageCaption +
                "</em></span><div>Figure " + display_str + ": " + imageCaption + "</div>")./*css({
                "position": "absolute",
                "top": positionTop + "px",
                "left": "0",
                "width": imgWidth + "px"
            }).* /insertAfter(this); */
        }
    });

}

$(window).on('load', function() {
    altToCaption();
});
