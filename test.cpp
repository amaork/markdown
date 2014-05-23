#include "markdown.h"

int main(int argc, char **argv)
{
	unsigned int idx;
	stringstream format;

	/* Create a markdown file */
	Markdown test("test.md");

	/* Anchor */
	test.add_anchor("这是一个内部锚，ID为start", "start");

	/* Write title 1 */
	test.add_h1("红色的标题1", "red");
	test.add_h2("绿色的标题2", "green");
	test.add_h3("蓝色的标题3", "blue");
	test.add_h4("紫色的标题4", "#FF00FF");
	test.add_h5("默认颜色的标题5");
	test.add_h6("默认颜色的标题6");

	/* Horizontal line */
	test.add_context("下面的是横向标尺语法:");
	test.add_hrule();

	/* Add strong */
	test.add_strong("这是一个粗体强调语法");
	test.add_emphasize("这是一个斜体强调语法");
	test.add_strikethrough("这是一个删除线语法");
	test.add_underline("这是一个下划线语法");

	/* subscript and superscript */
	test.add_context("这是一个上标语法: E = mc" + test.add_superscript("2"));
	test.add_context("这是一个下标语法: H" + test.add_subscript("2") + "O");


	/* Inline code and code block */
	test.add_context("\n下面的是嵌入代码语法：\n");	
	test.add_inline_code("int main(int argc, char **argv)");
	test.add_context("\n下面的是代码块语法：\n");
	test.add_code_block("int main(int argc, char **argv)");
	test.add_code_block("{");
	test.add_code_block("\tprintf(\"Hello Markdown\\n\");");
	test.add_code_block("\treturn 0;");
	test.add_code_block("}");

	/* Quote  */
	test.add_context("\n下面是是一个引用语法：\n");
	test.add_quote("这些内容是引用的内容");	
	test.add_context("\n下面是一个嵌套引用：\n");

	for (idx = 1; idx <= test.max_quote_level; idx++){

		format.str("");
		format << "这是一个" << idx << "级别嵌套引用";
		test.add_quote(format.str(), idx);
	}

	/* Commant */
	test.add_comment("这是一个注释，不会显示在HTML中");

	/* Color start */
	test.add_context("从下面开始文字将显示为红色的；");
	test.add_color_start("red");

	/* Ordered list */
	test.add_context("\n下面是有编号列表语法:\n");	

	for (idx = 1; idx <= 10; idx++){

		format.str("");
		format << "顺序列表，编号:" << idx;
		test.add_ordered_list(idx, format.str());
		test.add_ordered_list(1, "嵌套顺序列表1", 1);
		test.add_ordered_list(2, "嵌套顺序列表1", 1);
	}

	/* Color end */
	test.add_color_end();
	test.add_context("从下面开始文字将显示为蓝色的；");
	test.add_color_start("blue");

	/* Undered list */
	test.add_context("\n下面是无编号列表语法:\n");
	for (idx = 1; idx <= 10; idx++){

		test.add_unordered_list("无序列表");
		test.add_unordered_list("嵌套无序列表1", 1);
		test.add_unordered_list("嵌套无序列表1", 1);
	}
	
	/* Link */
	test.add_link("这是一个链接语法，指向该项目主页", "https://github.com/amaork/markdown");

	/* Image */
	test.add_context("下面的是一个图像链接语法，显示的是我的图像：");
	test.add_image("https://avatars2.githubusercontent.com/u/5653627?s=400", "avatars");

	/* Internal jump */
	test.add_intjump("这是一个文档内部跳转链接，可以跳转到文件的开始位置ID为start的锚", "start");

	/* Test auto image link detect */
	test.add_context("下面是用来测试add_context函数自动分析图片链接功能的:http://img3.douban.com/view/page_note/large/public/p28269709-1.jpg");
	test.add_context("http://img3.douban.com/view/page_note/large/public/p28269709-1.jpg图片链接测试https://github.com/amaork/markdown链接测试");

	return 0;
}
