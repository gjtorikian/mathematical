var debounce = function(fn) {
  var timeout;
  var slice = Array.prototype.slice;

  return function() {
    var args = slice.call(arguments),
        ctx = this;

    clearTimeout(timeout);

    timeout = setTimeout(function () {
      fn.apply(ctx, args);
    }, 100);
  };
};

$( document ).ready(function() {
  var demo = $('#demo-input');

  demo.bind('keyup', debounce(function() {
    var tex = demo.val();
    tex = $.trim(tex);
    tex = encodeURIComponent(tex);

    $.ajax({
      url: "http://127.0.0.1:9393/render?math=" + tex,
      type: "GET",
      dataType: "text",
      crossDomain: true
    })
      .done(function( data ) {
        data = "<div>" + data + "</div>";
        $( "#svg-container" ).html( data );
    });

  }));

});
