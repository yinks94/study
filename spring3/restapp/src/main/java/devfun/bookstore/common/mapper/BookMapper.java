package devfun.bookstore.common.mapper;

import java.util.List;

import devfun.bookstore.common.domain.Book;

public interface BookMapper {

    List<Book> select();

    Book selectByPrimaryKey(Long id);

    int insert(Book book);

    int updateByPrimaryKey(Book book);

    int deleteByPrimaryKey(Long id);
}