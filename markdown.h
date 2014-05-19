#ifndef _MARKDOWN_H_
#define _MARKDOWN_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

/* Markdown */
class Markdown{


	public:

		/* Constructor */
		~Markdown();
		Markdown(const string& filename);


		/* Methods */

		/* Title */
		string add_h1(const string& text="", const string& color="");
		string add_h2(const string& text="", const string& color="");
		string add_h3(const string& text="", const string& color="");
		string add_h4(const string& text="", const string& color="");
		string add_h5(const string& text="", const string& color="");
		string add_h6(const string& text="", const string& color="");
		string add_title(unsigned int level, const string& text="", const string& color="");

		/* Horizontal rules */
		string add_hrule(void);

		/* Strong (Blod)*/	
		string add_strong(const string& text);

		/* Emphasize (Italic)*/
		string add_emphasize(const string &text);

		/* Strikethrough */
		string add_strikethrough(const string &text);

		/* Underline */
		string add_underline(const string &text);

		/* Superscript */
		string add_superscript(const string& text);

		/* Subscript */
		string add_subscript(const string& text);

		/* Code */
		string add_code(const string& codes);
		
		/* Inline code */
		string add_inline_code(const string &codes);

		/* Quote */	
		string add_quote(const string& quote);

		/* Context */
		string add_context(const string& text, const string& color="");

		/* Comment */
		string add_comment(const string& comment);

		/* Ordered listss */
		string add_ordered_list(const vector<string> &lists);

		/* Unordered lists */
		string add_unordered_lists(const vector<string> &lists);
		
		/* Link */
		string add_link(const string& context, const string& link);

		/* Image */
		string add_image(const string& path, const string&alt_text="");

		/* Anchor and internal jump */
		string add_anchor(const string& context, const string& id);
		string add_intjump(const string& context, const string& jump_id);
	
	private:
		
		ofstream md_output;

		/* Output process */
		string output_process(const string& context);

		/* Font color analysic */
		string color_analysis(const string& context, const string& color);

		/* Syntax generator */
		string syntax_generator(const string& syntax, const string& data);
		string syntax_generator(const string& syntax, const string& attr, const string& data);

		/* Static data members */
		static const string title_syntax;
		static const string hrule_syntax;
		static const string strong_syntax;
		static const string emphasize_syntax;
		static const string underline_syntax;
		static const string strikethrough_syntax;
		static const string superscript_syntax;
		static const string subscript_syntax;
		static const string code_syntax;
		static const string inlinecode_syntax;
		static const string quote_syntax;
		static const string comment_syntax;
		static const string unorderedlist_syntax;
		static const string fontcolor_syntax;
		static const string link_syntax;
		static const string image_syntax;
		static const string anchor_syntax;
		static const string intjump_syntax;

		/* Syntax generator */
		static const string syntax_data;
		static const string syntax_attr;	
};

#endif
