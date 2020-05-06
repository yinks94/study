package devfun.bookstore.common.domain;

import java.util.Date;

import org.pojomatic.Pojomatic;
import org.pojomatic.annotations.AutoProperty;

@AutoProperty
public class Book {

    private Long id;
    private String title;
    private String creator;
    private String type;
    private Date date;

    /**
     * 
     */
    public Book() {
    }
    

    /**
     * @param id
     * @param title
     * @param creator
     * @param type
     * @param date
     */
    public Book(Long id, String title, String creator, String type, Date date) {
        this.id = id;
        this.title = title;
        this.creator = creator;
        this.type = type;
        this.date = date;
    }
    
    /**
     * @return the id
     */
    public Long getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(Long id) {
        this.id = id;
    }

    /**
     * @return the title
     */
    public String getTitle() {
        return title;
    }

    /**
     * @param title the title to set
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * @return the creator
     */
    public String getCreator() {
        return creator;
    }

    /**
     * @param creator the creator to set
     */
    public void setCreator(String creator) {
        this.creator = creator;
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type the type to set
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * @return the date
     */
    public Date getDate() {
        return date;
    }

    /**
     * @param date the date to set
     */
    public void setDate(Date date) {
        this.date = date;
    }

    @Override
    public boolean equals(Object obj) {
        return Pojomatic.equals(this, obj);
    }

    @Override
    public int hashCode() {
        return Pojomatic.hashCode(this);
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */

    @Override
    public String toString() {
        return Pojomatic.toString(this);
    }




    
    
}