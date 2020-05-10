package devfun.bookstore.common.service;

import java.util.List;

import devfun.bookstore.common.domain.Book;

public interface BookService {

    List<Book> getBooks();

    Book getBook(Long id);

    int createBook(Book book);

    int updateBook(Book book);

    int deleteBook(Long id);    
    
}