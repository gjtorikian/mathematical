module Mathematical
  class Math < HTML
    def self.to_html(node)
      # alttext = node.get_attribute("alttext")
# var alttext = this.Get("alttext");
        # if (alttext && alttext !== "") {node.setAttribute("aria-label",alttext)}
  # var nobr = HTMLCSS.addElement(span,"nobr",{isMathJax: true});
  # span = this.HTMLcreateSpan(nobr);
  # var stack = HTMLCSS.createStack(span), box = HTMLCSS.createBox(stack), math;
  # // Move font-size from outer span to stack to avoid line separation
  # // problem in strict HTML mode
  # stack.style.fontSize = nobr.parentNode.style.fontSize; nobr.parentNode.style.fontSize = "";
  # if (this.data[0] != null) {
  #   if (HTMLCSS.msieColorBug) {
  #     if (this.background) {this.data[0].background = this.background; delete this.background}
  #     if (this.mathbackground) {this.data[0].mathbackground = this.mathbackground; delete this.mathbackground}
  #   }
  #   MML.mbase.prototype.displayAlign = HUB.config.displayAlign;
  #   MML.mbase.prototype.displayIndent = HUB.config.displayIndent;
  #         var html = this.data[0].toHTML(box); html.bbox.exactW = false; // force remeasure just to be sure
  #   math = HTMLCSS.Measured(html,box);
  # }
  # HTMLCSS.placeBox(box,0,0);
  #       //
  #       //  Get width right if minimum font size is set:
  #       //    Round to nearest pixel (plus a small amount), and convert back to outer-em's.
  #       //    Add the width to the span (outside the MathJax class, so uses outer em size,
  #       //    which makes it work even when minimum font size is in effect).
  #       //
  #       span.style.width = HTMLCSS.Em((Math.round(math.bbox.w*this.em)+.25)/HTMLCSS.outerEm);
  #       span.style.display = "inline-block";
  # //
  # //  Adjust bbox to match outer em-size
  # //
  #       var p = 1/HTMLCSS.em, f = HTMLCSS.em / HTMLCSS.outerEm; HTMLCSS.em /= f;
  # span.bbox.h *= f; span.bbox.d *= f; span.bbox.w *= f;
  # span.bbox.lw *= f; span.bbox.rw *= f;
  # if (math && math.bbox.width != null) {
  #         span.style.minWidth = (math.bbox.minWidth || span.style.width);
  #   span.style.width = stack.style.width = math.bbox.width;
  #   box.style.width = "100%";
  # }
  # //
  # //  Add color (if any)
  # //
  # this.HTMLhandleColor(span);
  # //
  # //  Make math span be the correct height and depth
  # //
  # if (math) {HTMLCSS.createRule(span,(math.bbox.h+p)*f,(math.bbox.d+p)*f,0)}
  # //
  # //  Handle indentalign and indentshift for single-line display equations
  # //
  # if (!this.isMultiline && this.Get("display") === "block" && span.bbox.width == null) {
  #   var values = this.getValues("indentalignfirst","indentshiftfirst","indentalign","indentshift");
  #   if (values.indentalignfirst !== MML.INDENTALIGN.INDENTALIGN) {values.indentalign = values.indentalignfirst}
  #   if (values.indentalign === MML.INDENTALIGN.AUTO) {values.indentalign = this.displayAlign}
  #   node.style.textAlign = values.indentalign;
  #   if (values.indentshiftfirst !== MML.INDENTSHIFT.INDENTSHIFT) {values.indentshift = values.indentshiftfirst}
  #   if (values.indentshift === "auto") {values.indentshift = this.displayIndent}
  #   if (values.indentshift && values.indentalign !== MML.INDENTALIGN.CENTER) {
  #     span.style[{left:"marginLeft",right:"marginRight"}[values.indentalign]] =
  #       HTMLCSS.Em(HTMLCSS.length2em(values.indentshift));
  #   }
  # }
  # return span;
    end
  end
end