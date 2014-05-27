#ifndef _MARKDOWN_H_
#define _MARKDOWN_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<string> Md_list; 

/* Markdown */
class Markdown{


	public:

		/* Constructor */
		Markdown();
		~Markdown();
		Markdown(const string& filename);


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
		string add_superscript(const string& text, bool output=false);

		/* Subscript */
		string add_subscript(const string& text, bool output=false);

		/* Code */
		string add_code_block(const string& codes);
		
		/* Inline code */
		string add_inline_code(const string &codes);

		/* Quote */	
		string add_quote(const string& quote, const unsigned int level=1);

		/* Context */
		string add_context(const string& text, const string& color="");

		/* Comment */
		string add_comment(const string& comment);

		/* Link */
		string add_link(const string& context, const string& link);

		/* Image */
		string add_image(const string& path, const string& alt_text="");

		/* Anchor and internal jump */
		string add_anchor(const string& context, const string& id);
		string add_intjump(const string& context, const string& jump_id);

		/* Color start and end */
		string add_color_start(const string& color);
		string add_color_end(void);	

		/* Ordered listss */
		string add_ordered_list(const Md_list& list);
		string add_ordered_list(const Md_list& list, unsigned int level);
		string add_ordered_list(unsigned int index, const string& context, unsigned int level=0);

		/* Unordered lists */
		string add_unordered_list(const Md_list& list);
		string add_unordered_list(const Md_list& list, unsigned int level);
		string add_unordered_list(const string& item, unsigned int level=0);
		
		/* Syntax constract */
		static const unsigned int max_title_level;
		static const unsigned int max_quote_level;
		static const unsigned int max_nestedlist_level;
	
	private:
		
		ofstream md_output;

		/* Common init */
		void init(void);

		/* Int to string */
		inline string int_to_str(unsigned int number)
		{
			stringstream conv;
			conv << number;
			return conv.str();
		}

		/* Check if text is a url */
		bool is_a_url(const string& text);

		/* Check if text is image url */
		bool is_a_image(const string& text);

		/* Url analysis */
		string url_analysis(const string& text, const string& color);

		/* Output process */
		string output_process(const string& context, bool output=true);

		/* Font color analysic */
		string color_analysis(const string& context, const string& color);

		/* Syntax generator */
		string syntax_generator(const string& syntax, const string& data);
		string syntax_generator(const string& syntax, const string& attr, const string& data);
		string syntax_generator(const string& syntax, unsigned int level, unsigned int max_level, bool space=true);

		/* Static data members */
		static const string title_syntax;
		static const string hrule_syntax;
		static const string strong_syntax;
		static const string emphasize_syntax;
		static const string underline_syntax;
		static const string strikethrough_syntax;
		static const string superscript_syntax;
		static const string subscript_syntax;
		static const string codeblock_syntax;
		static const string inlinecode_syntax;
		static const string quote_syntax;
		static const string comment_syntax;
		static const string nestedlist_syntax;
		static const string orderedlist_syntax;
		static const string unorderedlist_syntax;
		static const string fontcolor_syntax;
		static const string color_start_syntax;
		static const string color_end_syntax;
		static const string link_syntax;
		static const string image_syntax;
		static const string anchor_syntax;
		static const string intjump_syntax;

		/* Syntax generator */
		static const string syntax_data;
		static const string syntax_attr;	

		/* Link and image analysis */
		string  split_ch;
		Md_list link_start;
		Md_list image_end;

};

#endif
