--  lists the names of songs that are by Post Malone
SELECT name FROM songs WHERE (SELECT id FROM artists WHERE name = 'Post Malone') = songs.artist_id;
