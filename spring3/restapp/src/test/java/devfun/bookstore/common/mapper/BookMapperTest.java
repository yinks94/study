package devfun.bookstore.common.mapper;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import java.util.Date;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import devfun.bookstore.common.config.AppConfig;
import devfun.bookstore.common.domain.Book;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = {AppConfig.class})
public class BookMapperTest {
    Logger logger = LoggerFactory.getLogger(BookMapperTest.class);

    @Autowired
    BookMapper bookMapper;

    @Test
    public void testBookMapper(){
        List<Book> books = bookMapper.select();
        assertEquals(3, books.size());
        for(Book book : books){
            logger.info("book={}", book);
        }

        Book newBook = new Book(10L, "스칼라 프로그래밍", "케이 호스트만", "프로그리맹 언어", new Date());
        bookMapper.insert(newBook);
        books = bookMapper.select();
        assertEquals(4, books.size());

        Book selectBook = bookMapper.selectByPrimaryKey(10L);
        logger.info("i.selectedBook={}", selectBook);
        assertEquals(newBook, selectBook);


        newBook.setCreator("나잘난");  
        bookMapper.updateByPrimaryKey(newBook);
        selectBook = bookMapper.selectByPrimaryKey(10L);
        logger.info("u.seletedBook={}", selectBook);
        assertEquals("나잘난", selectBook.getCreator());

        bookMapper.deleteByPrimaryKey(10L);
        selectBook = bookMapper.selectByPrimaryKey(10L);
        logger.info("d.selectedBook={}", selectBook);
        assertNull(selectBook);
    }
}