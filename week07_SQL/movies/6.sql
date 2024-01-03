SELECT AVG(rating)
  FROM ratings AS r
       JOIN movies AS m ON m.id = r.movie_id
 WHERE year = 2012;
