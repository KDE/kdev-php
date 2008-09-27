<?php
// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

class SWFText {
    /**
     * swftext-&gt;addstring draws the string string
     * at the current pen (cursor) location. Pen is at the baseline of the text; 
     * i.e., ascending text is in the -y direction.
     *
     * @param string
     * @return void
     **/
    function addString($string) {}

    /**
     * @param string
     * @return void
     **/
    function addUTF8String($text) {}

    /**
     * Creates a new SWFText object, fresh for 
     * manipulating.
     *
     * @return void
     **/
    function __construct() {}

    /**
     * @return float
     **/
    function getAscent() {}

    /**
     * @return float
     **/
    function getDescent() {}

    /**
     * @return float
     **/
    function getLeading() {}

    /**
     * @param string
     * @return float
     **/
    function getUTF8Width($string) {}

    /**
     * Returns the rendered width of the string at the
     * text object's current font, scale, and spacing settings.
     *
     * @param string
     * @return float
     **/
    function getWidth($string) {}

    /**
     * swftext-&gt;moveto moves the pen (or cursor, if 
     * that makes more sense) to (x,y)
     * in text object's coordinate space. If either is zero, though, value 
     * in that dimension stays the same. Annoying, should be fixed.
     *
     * @param int
     * @param int
     * @return void
     **/
    function moveTo($x, $y) {}

    /**
     * Changes the current text color.
     *
     * @param int
     * @param int
     * @param int
     * @param int
     * @return void
     **/
    function setColor($red, $green, $blue, $a) {}

    /**
     * swftext-&gt;setfont sets the current font to 
     * font.
     *
     * @param string
     * @return void
     **/
    function setFont($font) {}

    /**
     * swftext-&gt;setheight sets the current font height to 
     * height. Default is 240.
     *
     * @param int
     * @return void
     **/
    function setHeight($height) {}

    /**
     * swftext-&gt;setspacing sets the current font spacing to 
     * spacing. Default is 1.0. 
     * 0 is all of the letters written at the same point. This doesn't really work 
     * that well because it inflates the advance across the letter, doesn't add 
     * the same amount of spacing between the letters. I should try and explain 
     * that better, prolly. Or just fix the damn thing to do constant spacing. 
     * This was really just a way to figure out how letter advances work, 
     * anyway.. So nyah.
     *
     * @param float
     * @return void
     **/
    function setSpacing($spacing) {}

}
class SWFTextField {
    /**
     * @param string
     * @return void
     **/
    function addChars($chars) {}

    /**
     * swftextfield-&gt;setname concatenates the string
     * string to the text field.
     *
     * @param string
     * @return void
     **/
    function addString($string) {}

    /**
     * swftextfield-&gt;align sets the text field alignment
     * to alignement. Valid values for 
     * alignement are : SWFTEXTFIELD_ALIGN_LEFT, 
     * SWFTEXTFIELD_ALIGN_RIGHT, SWFTEXTFIELD_ALIGN_CENTER and 
     * SWFTEXTFIELD_ALIGN_JUSTIFY.
     *
     * @param int
     * @return void
     **/
    function align($alignement) {}

    /**
     * swftextfield creates a new text field object. 
     * Text Fields are less flexible than swftext objects- 
     * they can't be rotated, scaled non-proportionally, or skewed, but they can
     * be used as form entries, and they can use browser-defined fonts.
     *
     * @param int
     * @return SWFTextField
     **/
    function __construct($flags) {}

    /**
     * swftextfield-&gt;setbounds sets the text field width 
     * to width and height to height.
     * If you don't set the bounds yourself, Ming makes a poor guess at what 
     * the bounds are.
     *
     * @param int
     * @param int
     * @return void
     **/
    function setBounds($width, $height) {}

    /**
     * swftextfield-&gt;setcolor sets the color of the text field. 
     * Default is fully opaque black. Color is represented using RGB system.
     *
     * @param int
     * @param int
     * @param int
     * @param int
     * @return void
     **/
    function setColor($red, $green, $blue, $a) {}

    /**
     * swftextfield-&gt;setfont sets the text field font to 
     * the [browser-defined?] font font.
     *
     * @param string
     * @return void
     **/
    function setFont($font) {}

    /**
     * swftextfield-&gt;setheight sets the font height of this text field
     * font to the given height height. Default is 240.
     *
     * @param int
     * @return void
     **/
    function setHeight($height) {}

    /**
     * swftextfield-&gt;setindentation sets the indentation of 
     * the first line in the text field, to width.
     *
     * @param int
     * @return void
     **/
    function setIndentation($width) {}

    /**
     * swftextfield-&gt;setleftmargin sets the left margin width
     * of the text field to width. Default is 0.
     *
     * @param int
     * @return void
     **/
    function setLeftMargin($width) {}

    /**
     * swftextfield-&gt;setlinespacing sets the line spacing
     * of the text field to the height of height. Default is 40.
     *
     * @param int
     * @return void
     **/
    function setLineSpacing($height) {}

    /**
     * swftextfield-&gt;setmargins set both margins at once, 
     * for the man on the go.
     *
     * @param int
     * @param int
     * @return void
     **/
    function setMargins($left, $right) {}

    /**
     * swftextfield-&gt;setname sets the variable name of this
     * text field to name, for form posting and action 
     * scripting purposes.
     *
     * @param string
     * @return void
     **/
    function setName($name) {}

    /**
     * @param float
     * @return void
     **/
    function setPadding($padding) {}

    /**
     * swftextfield-&gt;setrightmargin sets the right margin width
     * of the text field to width. Default is 0.
     *
     * @param int
     * @return void
     **/
    function setRightMargin($width) {}

}
class SWFVideoStream {
    /**
     * @param string
     * @return SWFVideoStream
     **/
    function __construct($file) {}

    /**
     * This function returns the number of video-frames of a SWFVideoStream.
     *
     * @return int
     **/
    function getNumFrames() {}

    /**
     * Sets the width and height for streamed videos.
     *
     * @param int
     * @param int
     * @return void
     **/
    function setDimension($x, $y) {}

}
class MySQLi {
}
class MySQLi_Driver {
}
class MySQLi_Result {
}
class MySQLi_STMT {
}
class mysqli {
    /**
     * Object oriented style (method)
     *
     * @param bool
     * @return bool
     **/
    function autocommit($mode) {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @param string
     * @param string
     * @return bool
     **/
    function change_user($user, $password, $database) {}

    /**
     * Object oriented style (method):
     *
     * @return string
     **/
    function character_set_name() {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function close() {}

    /**
     * Object oriented style (method)
     *
     * @return bool
     **/
    function commit() {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @return bool
     **/
    function debug($message) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function dump_debug_info() {}

    /**
     * Returns a character set object providing several properties 
     * of the current active characer set.
     *
     * @return object
     **/
    function get_charset() {}

    /**
     * The mysqli_get_client_info function is used to
     * return a string representing the client version being used in the
     * MySQLi extension.
     *
     * @return string
     **/
    function get_client_info() {}

    /**
     * Returns client version number as an integer.
     *
     * @return int
     **/
    function get_client_version() {}

    /**
     * @return object
     **/
    function get_warnings() {}

    /**
     * Object oriented style (method)
     *
     * @param int
     * @return bool
     **/
    function kill($processid) {}

    /**
     * Indicates if one or more result sets are available from a previous call to
     * mysqli_multi_query.
     *
     * @return bool
     **/
    function more_results() {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @return bool
     **/
    function multi_query($query) {}

    /**
     * Prepares next result set from a previous call to 
     * mysqli_multi_query which can be retrieved by
     * mysqli_store_result or
     * mysqli_use_result.
     *
     * @return bool
     **/
    function next_result() {}

    /**
     * Object oriented style (method)
     *
     * @param int
     * @param mixed
     * @return bool
     **/
    function options($option, $value) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function ping() {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @param int
     * @return mixed
     **/
    function query($query, $resultmode) {}

    /**
     * Object oriented style (method)
     *
     * @param string
     * @param string
     * @param string
     * @param string
     * @param int
     * @param string
     * @param int
     * @return bool
     **/
    function real_connect($host, $username, $passwd, $dbname, $port, $socket, $flags) {}

    /**
     * Object oriented style (both methods are equivalent):
     *
     * @param string
     * @return string
     **/
    function escape_string($escapestr) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function rollback() {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @return bool
     **/
    function select_db($dbname) {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @return bool
     **/
    function set_charset($charset) {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @param string
     * @param string
     * @param string
     * @param string
     * @return bool
     **/
    function ssl_set($key, $cert, $ca, $capath, $cipher) {}

    /**
     * Object oriented style (method):
     *
     * @return string
     **/
    function stat() {}

}
class mysqli_driver {
    /**
     * @return void
     **/
    function embedded_server_end() {}

    /**
     * @param bool
     * @param array
     * @param array
     * @return bool
     **/
    function embedded_server_start($start, $arguments, $groups) {}

}
class mysqli_result {
    /**
     * Object oriented style (method):
     *
     * @param int
     * @return bool
     **/
    function data_seek($offset) {}

    /**
     * Object oriented style (method):
     *
     * @param int
     * @return mixed
     **/
    function fetch_array($resulttype) {}

    /**
     * Object oriented style (method):
     *
     * @return array
     **/
    function fetch_assoc() {}

    /**
     * Object oriented style (method):
     *
     * @param int
     * @return object
     **/
    function fetch_field_direct($fieldnr) {}

    /**
     * Object oriented style (method):
     *
     * @return object
     **/
    function fetch_field() {}

    /**
     * Object oriented style (method):
     *
     * @return array
     **/
    function fetch_fields() {}

    /**
     * Object oriented style (method):
     *
     * @param string
     * @param array
     * @return object
     **/
    function fetch_object($class_name, $params) {}

    /**
     * Object oriented style (method):
     *
     * @return mixed
     **/
    function fetch_row() {}

    /**
     * Object oriented style (method):
     *
     * @param int
     * @return bool
     **/
    function field_seek($fieldnr) {}

    /**
     * Object oriented style (all methods are equivalent):
     *
     * @return void
     **/
    function free() {}

}
class mysqli_stmt {
    /**
     * Object oriented style (method):
     *
     * @param string
     * @param mixed
     * @return bool
     **/
    function bind_param($types, $var1) {}

    /**
     * Object oriented style (method):
     *
     * @param mixed
     * @return bool
     **/
    function bind_result($var1) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function close() {}

    /**
     * Object oriented style (method):
     *
     * @param int
     * @return void
     **/
    function data_seek($offset) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function execute() {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function fetch() {}

    /**
     * Object oriented style (method):
     *
     * @return void
     **/
    function free_result() {}

    /**
     * @param mysqli_stmt
     * @return object
     **/
    function get_warnings($stmt) {}

    /**
     * Object oriented style (method)
     *
     * @param string
     * @return mixed
     **/
    function prepare($query) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function reset() {}

    /**
     * Object oriented style (method):
     *
     * @return mysqli_result
     **/
    function result_metadata() {}

    /**
     * Object oriented style (method)
     *
     * @param int
     * @param string
     * @return bool
     **/
    function send_long_data($param_nr, $data) {}

    /**
     * Object oriented style (method):
     *
     * @return bool
     **/
    function store_result() {}

}
class PDO {
    const PARAM_BOOL = 0;
    const PARAM_NULL = 0;
    const PARAM_INT = 0;
    const PARAM_STR = 0;
    const PARAM_LOB = 0;
    const PARAM_STMT = 0;
    const PARAM_INPUT_OUTPUT = 0;
    const FETCH_LAZY = 0;
    const FETCH_ASSOC = 0;
    const FETCH_NAMED = 0;
    const FETCH_NUM = 0;
    const FETCH_BOTH = 0;
    const FETCH_OBJ = 0;
    const FETCH_BOUND = 0;
    const FETCH_COLUMN = 0;
    const FETCH_CLASS = 0;
    const FETCH_INTO = 0;
    const FETCH_FUNC = 0;
    const FETCH_GROUP = 0;
    const FETCH_UNIQUE = 0;
    const FETCH_KEY_PAIR = 0;
    const FETCH_CLASSTYPE = 0;
    const FETCH_SERIALIZE = 0;
    const FETCH_PROPS_LATE = 0;
    const ATTR_AUTOCOMMIT = 0;
    const ATTR_PREFETCH = 0;
    const ATTR_TIMEOUT = 0;
    const ATTR_ERRMODE = 0;
    const ATTR_SERVER_VERSION = 0;
    const ATTR_CLIENT_VERSION = 0;
    const ATTR_SERVER_INFO = 0;
    const ATTR_CONNECTION_STATUS = 0;
    const ATTR_CASE = 0;
    const ATTR_CURSOR_NAME = 0;
    const ATTR_CURSOR = 0;
    const ATTR_DRIVER_NAME = '';
    const ATTR_ORACLE_NULLS = 0;
    const ATTR_PERSISTENT = 0;
    const ATTR_STATEMENT_CLASS = 0;
    const ATTR_FETCH_CATALOG_NAMES = 0;
    const ATTR_FETCH_TABLE_NAMES = 0;
    const ATTR_STRINGIFY_FETCHES = 0;
    const ATTR_MAX_COLUMN_LEN = 0;
    const ATTR_DEFAULT_FETCH_MODE = 0;
    const ATTR_EMULATE_PREPARES = 0;
    const ERRMODE_SILENT = 0;
    const ERRMODE_WARNING = 0;
    const ERRMODE_EXCEPTION = 0;
    const CASE_NATURAL = 0;
    const CASE_LOWER = 0;
    const CASE_UPPER = 0;
    const NULL_NATURAL = 0;
    const NULL_EMPTY_STRING = 0;
    const NULL_TO_STRING = 0;
    const FETCH_ORI_NEXT = 0;
    const FETCH_ORI_PRIOR = 0;
    const FETCH_ORI_FIRST = 0;
    const FETCH_ORI_LAST = 0;
    const FETCH_ORI_ABS = 0;
    const FETCH_ORI_REL = 0;
    const CURSOR_FWDONLY = 0;
    const CURSOR_SCROLL = 0;
    const ERR_NONE = '';
    const PARAM_EVT_ALLOC = 0;
    const PARAM_EVT_FREE = 0;
    const PARAM_EVT_EXEC_PRE = 0;
    const PARAM_EVT_EXEC_POST = 0;
    const PARAM_EVT_FETCH_PRE = 0;
    const PARAM_EVT_FETCH_POST = 0;
    const PARAM_EVT_NORMALIZE = 0;
    const MYSQL_ATTR_USE_BUFFERED_QUERY = 0;
    const MYSQL_ATTR_LOCAL_INFILE = 0;
    const MYSQL_ATTR_INIT_COMMAND = 0;
    const MYSQL_ATTR_READ_DEFAULT_FILE = 0;
    const MYSQL_ATTR_READ_DEFAULT_GROUP = 0;
    const MYSQL_ATTR_MAX_BUFFER_SIZE = 0;
    const MYSQL_ATTR_DIRECT_QUERY = 0;
    /**
     * Turns off autocommit mode. While autocommit mode is turned off, changes
     * made to the database via the PDO object instance are not committed until
     * you end the transaction by calling PDO::commit.
     * Calling PDO::rollBack will roll back all changes to
     * the database and return the connection to autocommit mode.
     *
     * @return bool
     **/
    function beginTransaction() {}

    /**
     * Commits a transaction, returning the database connection to autocommit
     * mode until the next call to PDO::beginTransaction
     * starts a new transaction.
     *
     * @return bool
     **/
    function commit() {}

    /**
     * @return string
     **/
    function errorCode() {}

    /**
     * @return array
     **/
    function errorInfo() {}

    /**
     * PDO::exec executes an SQL statement in
     * a single function call, returning the number of rows affected by the
     * statement.
     *
     * @param string
     * @return int
     **/
    function exec($statement) {}

    /**
     * This function returns the value of a database connection attribute. To
     * retrieve PDOStatement attributes, refer to
     * PDOStatement::getAttribute.
     *
     * @param int
     * @return mixed
     **/
    function getAttribute($attribute) {}

    /**
     * This function returns all currently available PDO drivers which can be used
     * in DSN parameter of
     * PDO::__construct. This is a static method.
     *
     * @return array
     **/
    function getAvailableDrivers() {}

    /**
     * Returns the ID of the last inserted row, or the last value from a
     * sequence object, depending on the underlying driver. For example,
     * PDO_PGSQL requires you to specify the name of
     * a sequence object for the name parameter.
     *
     * @param string
     * @return string
     **/
    function lastInsertId($name) {}

    /**
     * Prepares an SQL statement to be executed by the
     * PDOStatement::execute method. The SQL statement can
     * contain zero or more named (:name) or question mark (?) parameter markers
     * for which real values will be substituted when the statement is executed.
     * You cannot use both named and question mark parameter markers within the same
     * SQL statement; pick one or the other parameter style.
     *
     * @param string
     * @param array
     * @return PDOStatement
     **/
    function prepare($statement, $driver_options) {}

    /**
     * PDO::query executes an SQL statement in
     * a single function call, returning the result set (if any) returned by the
     * statement as a PDOStatement object.
     *
     * @param string
     * @return PDOStatement
     **/
    function query($statement) {}

    /**
     * PDO::quote places quotes around the input string (if
     * required) and escapes special characters within the input string, using a
     * quoting style appropriate to the underlying driver.
     *
     * @param string
     * @param int
     * @return string
     **/
    function quote($string, $parameter_type) {}

    /**
     * Rolls back the current transaction, as initiated by
     * PDO::beginTransaction. It is an error to call this
     * method if no transaction is active.
     *
     * @return bool
     **/
    function rollBack() {}

    /**
     * Sets an attribute on the database handle. Some of the available generic
     * attributes are listed below; some drivers may make use of
     * additional driver specific attributes.
     * 
     * 
     * PDO::ATTR_CASE: Force column names to a specific case.
     * 
     * 
     * PDO::CASE_LOWER: Force column names to lower case.
     * 
     * 
     * PDO::CASE_NATURAL: Leave column names as returned by
     * the database driver.
     * 
     * 
     * PDO::CASE_UPPER: Force column names to upper case.
     * 
     * 
     * 
     * PDO::ATTR_ERRMODE: Error reporting.
     * 
     * PDO::ERRMODE_SILENT:
     * Just set error codes.
     * PDO::ERRMODE_WARNING:
     * Raise E_WARNING.
     * PDO::ERRMODE_EXCEPTION:
     * Throw exceptions.
     * 
     * 
     * PDO::ATTR_ORACLE_NULLS
     * (available with all drivers, not just Oracle):
     * Conversion of NULL and empty strings.
     * 
     * PDO::NULL_NATURAL:
     * No conversion.
     * PDO::NULL_EMPTY_STRING:
     * Empty string is converted to .
     * PDO::NULL_TO_STRING:
     * NULL is converted to an empty string.
     * 
     * 
     * PDO::ATTR_STRINGIFY_FETCHES:
     * Convert numeric values to strings when fetching.
     * Requires bool.
     * 
     * PDO::ATTR_STATEMENT_CLASS:
     * Set user-supplied statement class derived from PDOStatement.
     * Cannot be used with persistent PDO instances.
     * Requires array(string classname, array(mixed constructor_args)).
     * 
     * PDO::ATTR_AUTOCOMMIT
     * (available in OCI, Firebird and MySQL):
     * Whether to autocommit every single statement.
     * 
     * PDO::MYSQL_ATTR_USE_BUFFERED_QUERY
     * (available in MySQL):
     * Use buffered queries.
     *
     * @param int
     * @param mixed
     * @return bool
     **/
    function setAttribute($attribute, $value) {}

    /**
     * PDO::pgsqlLOBCreate creates a large object and
     * returns the OID of that object. You may then open a stream on the object
     * using PDO::pgsqlLOBOpen to read or write data to
     * it. The OID can be stored in columns of type OID and be used to reference
     * the large object, without causing the row to grow arbitrarily large.
     * The large object will continue to live in the database until it
     * is removed by calling PDO::pgsqlLOBUnlink.
     *
     * @return string
     **/
    function pgsqlLOBCreate() {}

    /**
     * PDO::pgsqlLOBOpen opens a stream to access the data
     * referenced by oid. If mode
     * is r, the stream is opened for reading, if
     * mode is w, then the stream will
     * be opened for writing. You can use all the usual filesystem functions,
     * such as fread, fwrite and
     * fgets to manipulate the contents of the stream.
     *
     * @param string
     * @param string
     * @return resource
     **/
    function pgsqlLOBOpen($oid, $mode) {}

    /**
     * Deletes a large object from the database identified by OID.
     *
     * @param string
     * @return bool
     **/
    function pgsqlLOBUnlink($oid) {}

    /**
     * This method is similar to except that it registers functions that can be used to calculate a
     * result aggregated across all the rows of a query.
     *
     * @param string
     * @param callback
     * @param callback
     * @param int
     * @return bool
     **/
    function sqliteCreateAggregate($function_name, $step_func, $finalize_func, $num_args) {}

    /**
     * This method allows you to register a PHP function with SQLite as an 
     * UDF (User Defined Function), so that it can be called
     * from within your SQL statements.
     *
     * @param string
     * @param callback
     * @param int
     * @return bool
     **/
    function sqliteCreateFunction($function_name, $callback, $num_args) {}

}
class PDOException extends RuntimeException {
}
class PDOStatement implements Traversable {
    /**
     * PDOStatement::bindColumn arranges to have a
     * particular variable bound to a given column in the result-set from a
     * query. Each call to PDOStatement::fetch or
     * PDOStatement::fetchAll will update all the variables
     * that are bound to columns.
     *
     * @param mixed
     * @param mixed
     * @param int
     * @param int
     * @param mixed
     * @return bool
     **/
    function bindColumn($column, $param, $type, $maxlen, $driverdata) {}

    /**
     * Binds a PHP variable to a corresponding named or question mark placeholder
     * in the SQL statement that was use to prepare the statement. Unlike
     * PDOStatement::bindValue, the variable is bound as a
     * reference and will only be evaluated at the time that
     * PDOStatement::execute is called.
     *
     * @param mixed
     * @param mixed
     * @param int
     * @param int
     * @param mixed
     * @return bool
     **/
    function bindParam($parameter, $variable, $data_type, $length, $driver_options) {}

    /**
     * Binds a value to a corresponding named or question mark placeholder
     * in the SQL statement that was use to prepare the statement.
     *
     * @param mixed
     * @param mixed
     * @param int
     * @return bool
     **/
    function bindValue($parameter, $value, $data_type) {}

    /**
     * PDOStatement::closeCursor frees up the connection
     * to the server so that other SQL statements may be issued, but leaves the
     * statement in a state that enables it to be executed again.
     *
     * @return bool
     **/
    function closeCursor() {}

    /**
     * Use PDOStatement::columnCount to return the number
     * of columns in the result set represented by the PDOStatement object.
     *
     * @return int
     **/
    function columnCount() {}

    /**
     * @return string
     **/
    function errorCode() {}

    /**
     * @return array
     **/
    function errorInfo() {}

    /**
     * Execute the prepared statement. If the prepared statement included
     * parameter markers, you must either:
     * 
     * call PDOStatement::bindParam to bind PHP variables
     * to the parameter markers: bound variables pass their value as input and receive the
     * output value, if any, of their associated parameter markers
     * or pass an array of input-only parameter values
     *
     * @param array
     * @return bool
     **/
    function execute($input_parameters) {}

    /**
     * Fetches a row from a result set associated with a PDOStatement object. The
     * fetch_style parameter determines how PDO returns
     * the row.
     *
     * @param int
     * @param int
     * @param int
     * @return mixed
     **/
    function fetch($fetch_style, $cursor_orientation, $cursor_offset) {}

    /**
     * @param int
     * @param int
     * @param array
     * @return array
     **/
    function fetchAll($fetch_style, $column_index, $ctor_args) {}

    /**
     * Returns a single column from the next row of a result set or if
     * there are no more rows.
     *
     * @param int
     * @return string
     **/
    function fetchColumn($column_number) {}

    /**
     * Fetches the next row and returns it as an object. This function is an
     * alternative to PDOStatement::fetch with
     * PDO::FETCH_CLASS or
     * PDO::FETCH_OBJ style.
     *
     * @param string
     * @param array
     * @return mixed
     **/
    function fetchObject($class_name, $ctor_args) {}

    /**
     * Gets an attribute of the statement. Currently, no generic attributes exist but only driver specific:
     * 
     * PDO::ATTR_CURSOR_NAME
     * (Firebird and ODBC specific):
     * Get the name of cursor for UPDATE ... WHERE CURRENT OF.
     *
     * @param int
     * @return mixed
     **/
    function getAttribute($attribute) {}

    /**
     * Retrieves the metadata for a 0-indexed column in a result set as an
     * associative array.
     *
     * @param int
     * @return array
     **/
    function getColumnMeta($column) {}

    /**
     * Some database servers support stored procedures that return more than one
     * rowset (also known as a result set).
     * PDOStatement::nextRowset enables you to access the
     * second and subsequent rowsets associated with a PDOStatement object. Each
     * rowset can have a different set of columns from the preceding rowset.
     *
     * @return bool
     **/
    function nextRowset() {}

    /**
     * PDOStatement::rowCount returns the number of
     * rows affected by the last DELETE, INSERT, or UPDATE statement
     * executed by the corresponding PDOStatement object.
     *
     * @return int
     **/
    function rowCount() {}

    /**
     * Sets an attribute on the statement. Currently, no generic attributes are set but only driver specific:
     * 
     * PDO::ATTR_CURSOR_NAME
     * (Firebird and ODBC specific):
     * Set the name of cursor for UPDATE ... WHERE CURRENT OF.
     *
     * @param int
     * @param mixed
     * @return bool
     **/
    function setAttribute($attribute, $value) {}

    /**
     * @param int
     * @return bool
     **/
    function setFetchMode($mode) {}

}
class Phar extends DirectoryIterator implements Countable, ArrayAccess {
    /**
     * With this method, an empty directory is created with path dirname.
     * This method is similar to ZipArchive::addEmptyDir.
     *
     * @param string
     * @return bool
     **/
    function addEmptyDir($dirname) {}

    /**
     * With this method, any file or URL can be added to the phar archive. If
     * the optional second parameter localname is specified,
     * the file will be stored in the archive with that name, otherwise the
     * file parameter is used as the path to store within
     * the archive. URLs must have a localname or an exception is thrown.
     * This method is similar to ZipArchive::addFile.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function addFile($file, $localname) {}

    /**
     * With this method, any string can be added to the phar archive.
     * The file will be stored in the archive with localname as its
     * path. This method is similar to ZipArchive::addFromString.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function addFromString($localname, $contents) {}

    /**
     * Return the API version of the phar file format that will be
     * used when creating phars. The Phar extension supports reading API
     * version 1.0.0 or newer. API version 1.1.0 is required for SHA-256 and SHA-512
     * hash, and API version 1.1.1 is required to store empty directories.
     *
     * @return string
     **/
    function apiVersion() {}

    /**
     * Populate a phar archive from directory contents. The optional second
     * parameter is a regular expression (pcre) that is used to exclude files.
     * Any filename that matches the regular expression will be included, all others will be
     * excluded. For more fine-grained control, use Phar::buildFromIterator.
     *
     * @param string
     * @param string
     * @return array
     **/
    function buildFromDirectory($base_dir, $regex) {}

    /**
     * Populate a phar archive from an iterator. Two styles of iterators are supported,
     * iterators that map the filename within the phar to the name of a file on disk,
     * and iterators like DirectoryIterator that return
     * SplFileInfo objects. For iterators that return SplFileInfo objects, the second
     * parameter is required.
     *
     * @param Iterator
     * @param string
     * @return array
     **/
    function buildFromIterator($iter, $base_directory) {}

    /**
     * This should be used to test whether compression is possible prior to
     * loading a phar archive containing compressed files.
     *
     * @param int
     * @return bool
     **/
    function canCompress($type) {}

    /**
     * This static method determines whether write access has been disabled in
     * the system php.ini via the phar.readonly
     * ini variable.
     *
     * @return bool
     **/
    function canWrite() {}

    /**
     * For tar-based and phar-based phar archives, this method compresses the entire archive using
     * gzip compression or bzip2 compression. The resulting file can be processed with the
     * gunzip command/bunzip command, or accessed directly and transparently with the Phar
     * extension.
     *
     * @param int
     * @param string
     * @return object
     **/
    function compress($compression, $extension) {}

    /**
     * This method compresses all files in the Phar archive using bzip2 compression.
     * The bzip2 extension must be enabled to take
     * advantage of this feature. In addition, if any files are already compressed using
     * gzip compression, the zlib extension must be enabled in order
     * to decompress the files prior to re-compressing with bzip2 compression.
     * As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed.
     *
     * @return bool
     **/
    function compressAllFilesBZIP2() {}

    /**
     * For tar-based phar archives, this method compresses the entire archive using
     * gzip compression. The resulting file can be processed with the gunzip command, or
     * accessed directly and transparently with the Phar extension.
     *
     * @return bool
     **/
    function compressAllFilesGZ() {}

    /**
     * For tar-based phar archives, this method throws a
     * BadMethodCallException, as compression of individual
     * files within a tar archive is not supported by the file format. Use
     * Phar::compress to compress an entire tar-based phar archive.
     *
     * @param int
     * @return bool
     **/
    function compressFiles($compression) {}

    /**
     * @param string
     * @param int
     * @param string
     * @return void
     **/
    function __construct($fname, $flags, $alias) {}

    /**
     * This method is used to convert an executable phar archive to either a
     * tar or zip file. To make the tar or zip non-executable, the phar
     * stub and phar alias files are removed from the newly created archive.
     *
     * @param int
     * @param int
     * @param string
     * @return PharData
     **/
    function convertToData($format, $compression, $extension) {}

    /**
     * This method is used to convert a phar archive to another file format. For instance,
     * it can be used to create a tar-based executable phar archive from a zip-based
     * executable phar archive, or from an executable phar archive in the phar file format. In
     * addition, it can be used to apply whole-archive compression to a tar or phar-based
     * archive.
     *
     * @param int
     * @param int
     * @param string
     * @return Phar
     **/
    function convertToExecutable($format, $compression, $extension) {}

    /**
     * Copy a file internal to the phar archive to another new file within the phar.
     * This is an object-oriented alternative to using copy with
     * the phar stream wrapper.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function copy($oldfile, $newfile) {}

    /**
     * @return int
     **/
    function count() {}

    /**
     * This method is intended for creation of phar-file format-specific stubs, and is
     * not intended for use with tar- or zip-based phar archives.
     *
     * @return string
     **/
    function createDefaultStub() {}

    /**
     * For tar-based and phar-based phar archives, this method decompresses the entire archive.
     *
     * @param string
     * @return object
     **/
    function decompress($extension) {}

    /**
     * For tar-based phar archives, this method throws a
     * BadMethodCallException, as compression of individual
     * files within a tar archive is not supported by the file format. Use
     * Phar::compress to compress an entire tar-based phar archive.
     *
     * @return bool
     **/
    function decompressFiles() {}

    /**
     * Deletes the global metadata of the phar
     *
     * @return int
     **/
    function delMetadata() {}

    /**
     * Delete a file within an archive. This is the functional equivalent of
     * calling unlink on the stream wrapper equivalent,
     * as shown in the example below.
     *
     * @param string
     * @return int
     **/
    function delete($entry) {}

    /**
     * Extract all files within a phar archive to disk. Extracted files and directories preserve
     * permissions as stored in the archive. The optional parameters allow optional control over
     * which files are extracted, and whether existing files on disk can be overwritten.
     * The second parameter files can be either the name of a file or
     * directory to extract, or an array of names of files and directories to extract. By
     * default, this method will not overwrite existing files, the third parameter can be
     * set to true to enable overwriting of files.
     * This method is similar to ZipArchive::extractTo.
     *
     * @param string
     * @param string|array
     * @param bool
     * @return int
     **/
    function extractTo($pathto, $files, $overwrite) {}

    /**
     * Retrieve archive meta-data. Meta-data can be any PHP variable that can be serialized.
     *
     * @return int
     **/
    function getMetaData() {}

    /**
     * This method can be used to determine whether a phar has either
     * had an internal file deleted, or contents of a file changed in
     * some way.
     *
     * @return bool
     **/
    function getModified() {}

    /**
     * Returns the verification signature of a phar archive in a hexadecimal string.
     *
     * @return array
     **/
    function getSignature() {}

    /**
     * Phar archives contain a bootstrap loader, or stub
     * written in PHP that is executed when the archive is executed in PHP either via
     * include:
     * 
     * 
     * 
     * or by simple execution:
     *
     * @return string
     **/
    function getStub() {}

    /**
     * @return array
     **/
    function getSupportedCompression() {}

    /**
     * Return array of supported signature types
     *
     * @return array
     **/
    function getSupportedSignatures() {}

    /**
     * Returns the API version of an opened Phar archive.
     *
     * @return string
     **/
    function getVersion() {}

    /**
     * Returns whether phar has global meta-data set.
     *
     * @return int
     **/
    function hasMetadata() {}

    /**
     * instructs phar to intercept fopen, readfile,
     * file_get_contents, opendir, and all of
     * the stat-related functions. If any of these functions is called from within
     * a phar archive with a relative path, the call is modified to access a file
     * within the phar archive. Absolute paths are assumed to be attempts to load
     * external files from the filesystem.
     *
     * @return void
     **/
    function interceptFileFuncs() {}

    /**
     * This method can be used to determine whether a Phar will save changes
     * to disk immediately, or whether a call to Phar-stopBuffering
     * is needed to enable saving changes.
     *
     * @return bool
     **/
    function isBuffering() {}

    /**
     * Returns Phar::GZ or PHAR::BZ2 if the entire phar archive is compressed
     * (.tar.gz/tar.bz and so on). Zip-based phar archives cannot be compressed as a
     * file, and so this method will always return if a zip-based phar archive is queried.
     *
     * @return mixed
     **/
    function isCompressed() {}

    /**
     * @param int
     * @return bool
     **/
    function isFileFormat($format) {}

    /**
     * Returns whether the given filename is a valid phar filename that will be recognized
     * as a phar archive by the phar extension. This can be used to test a name without
     * having to instantiate a phar archive and catch the inevitable Exception that will be
     * thrown if an invalid name is specified.
     *
     * @param string
     * @param bool
     * @return bool
     **/
    function isValidPharFilename($filename, $executable) {}

    /**
     * This method returns if phar.readonly is 0,
     * and the actual phar archive on disk is not read-only.
     *
     * @return bool
     **/
    function isWritable() {}

    /**
     * This can be used to read the contents of an external Phar archive. This
     * is most useful for assigning an alias to a phar so that subsequent references
     * to the phar can use the shorter alias, or for loading Phar archives that
     * only contain data and are not intended for execution/inclusion in PHP scripts.
     *
     * @param string
     * @param string
     * @return mixed
     **/
    function loadPhar($filename, $alias) {}

    /**
     * This static method can only be used inside a Phar archive's loader stub
     * in order to initialize the phar when it is directly executed, or when
     * it is included in another script.
     *
     * @param string
     * @param int
     * @return mixed
     **/
    function mapPhar($alias, $dataoffset) {}

    /**
     * Much like the unix file system concept of mounting external devices to paths within the
     * directory tree, Phar::mount allows referring to external files
     * and directories as if they were inside of an archive. This allows powerful
     * abstraction such as referring to external configuration files as if they were
     * inside the archive.
     *
     * @param string
     * @param string
     * @return void
     **/
    function mount($pharpath, $externalpath) {}

    /**
     * Phar::mungServer should only be called within the
     * stub of a phar archive.
     *
     * @param array
     * @return void
     **/
    function mungServer($munglist) {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a Phar archive using
     * array access brackets.
     *
     * @param string
     * @return bool
     **/
    function offsetExists($offset) {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a Phar archive using
     * array access brackets. offsetGet is used for retrieving files from
     * a Phar archive.
     *
     * @param string
     * @return int
     **/
    function offsetGet($offset) {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a Phar archive using
     * array access brackets. offsetSet is used for modifying an
     * existing file, or adding a new file to a Phar archive.
     *
     * @param string
     * @param string
     * @return void
     **/
    function offsetSet($offset, $value) {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a Phar archive using
     * array access brackets. offsetUnset is used for deleting an
     * existing file, and is called by the unset
     * language construct.
     *
     * @param string
     * @return bool
     **/
    function offsetUnset($offset) {}

    /**
     * Returns the full path to the running phar archive. This is intended for use much
     * like the __FILE__ magic constant, and only has effect inside
     * an executing phar archive.
     *
     * @param bool
     * @return bool
     **/
    function running($retphar) {}

    /**
     * Set the alias for the Phar archive, and write it as the permanent alias
     * for this phar archive. An alias can be used internally to a phar archive to
     * ensure that use of the phar stream wrapper to access internal
     * files always works regardless of the location of the phar archive on the
     * filesystem. Another alternative is to rely upon Phar's interception of
     * include or to use Phar::interceptFileFuncs
     * and use relative paths.
     *
     * @param string
     * @return bool
     **/
    function setAlias($alias) {}

    /**
     * This method is a convenience method that combines the functionality of
     * Phar::createDefaultStub and Phar::setStub.
     *
     * @param string
     * @param string
     * @return void
     **/
    function setDefaultStub($index, $webindex) {}

    /**
     * Phar::setMetadata should be used to store customized data
     * that describes something about the phar archive as a complete entity.
     * PharFileInfo::setMetadata should be used for file-specific meta-data.
     * Meta-data can slow down the performance of loading a phar archive if the data is large.
     *
     * @param mixed
     * @return void
     **/
    function setMetadata($metadata) {}

    /**
     * set the signature algorithm for a phar and apply it. The
     * signature algorithm must be one of Phar::MD5,
     * Phar::SHA1, Phar::SHA256,
     * Phar::SHA512, or Phar::OPENSSL.
     *
     * @param int
     * @param string
     * @return array
     **/
    function setSignatureAlgorithm($sigtype, $privatekey) {}

    /**
     * This method is used to add a PHP bootstrap loader stub to a new Phar archive, or
     * to replace the loader stub in an existing Phar archive.
     *
     * @param string
     * @return void
     **/
    function setStub($stub) {}

    /**
     * Although technically unnecessary, the startBuffering method
     * can provide a significant performance boost when creating or modifying a
     * Phar archive with a large number of files. Ordinarily, every time a file
     * within a Phar archive is created or modified in any way, the entire Phar
     * archive will be recreated with the changes. In this way, the archive will
     * be up-to-date with the activity performed on it.
     *
     * @return void
     **/
    function startBuffering() {}

    /**
     * stopBuffering is used in conjunction with the
     * startBuffering method. startBuffering
     * can provide a significant performance boost when creating or modifying a
     * Phar archive with a large number of files. Ordinarily, every time a file
     * within a Phar archive is created or modified in any way, the entire Phar
     * archive will be recreated with the changes. In this way, the archive will
     * be up-to-date with the activity performed on it.
     *
     * @return void
     **/
    function stopBuffering() {}

    /**
     * This method decompresses all files in the Phar archive.
     * If any files are already compressed using
     * gzip compression, the zlib extension must be enabled in order
     * to decompress the files, and any files compressed using bzip2 compression
     * require the bzip2 extension to decompress the files.
     * As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed.
     *
     * @return bool
     **/
    function uncompressAllFiles() {}

    /**
     * @param string
     * @return bool
     **/
    function unlinkArchive($archive) {}

    /**
     * Phar::mapPhar for web-based phars. This method parses
     * $_SERVER['REQUEST_URI'] and routes a request from a web
     * browser to an internal file within the phar archive. In essence, it simulates
     * a web server, routing requests to the correct file, echoing the correct headers
     * and parsing PHP files as needed. This powerful method is part of what makes it easy
     * to convert an existing PHP application into a phar archive. Combined with
     * Phar::mungServer and Phar::interceptFileFuncs,
     * any web application can be used unmodified from a phar archive.
     *
     * @param string
     * @param string
     * @param string
     * @param array
     * @param array
     * @return void
     **/
    function webPhar($alias, $index, $f404, $mimetypes, $rewrites) {}

}
class PharData extends Phar {
    /**
     * With this method, an empty directory is created with path dirname.
     * This method is similar to ZipArchive::addEmptyDir.
     *
     * @param string
     * @return bool
     **/
    function addEmptyDir($dirname) {}

    /**
     * With this method, any string can be added to the tar/zip archive.
     * The file will be stored in the archive with localname as its
     * path. This method is similar to ZipArchive::addFromString.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function addFromString($localname, $contents) {}

    /**
     * Populate a tar or zip archive from an iterator. Two styles of iterators are supported,
     * iterators that map the filename within the tar/zip to the name of a file on disk,
     * and iterators like DirectoryIterator that return
     * SplFileInfo objects. For iterators that return SplFileInfo objects, the second
     * parameter is required.
     *
     * @param Iterator
     * @param string
     * @return array
     **/
    function buildFromIterator($iter, $base_directory) {}

    /**
     * For tar archives, this method compresses the entire archive using
     * gzip compression or bzip2 compression. The resulting file can be processed with the
     * gunzip command/bunzip command, or accessed directly and transparently with the Phar
     * extension.
     *
     * @param int
     * @param string
     * @return object
     **/
    function compress($compression, $extension) {}

    /**
     * For tar-based archives, this method throws a
     * BadMethodCallException, as compression of individual
     * files within a tar archive is not supported by the file format. Use
     * PharData::compress to compress an entire tar-based archive.
     *
     * @param int
     * @return bool
     **/
    function compressFiles($compression) {}

    /**
     * @param string
     * @param int
     * @return void
     **/
    function __construct($fname, $flags) {}

    /**
     * This method is used to convert a non-executable tar or zip archive to another
     * non-executable format.
     *
     * @param int
     * @param int
     * @param string
     * @return PharData
     **/
    function convertToData($format, $compression, $extension) {}

    /**
     * This method is used to convert a non-executable tar or zip archive to an
     * executable phar archive. Any of the three executable file formats
     * (phar, tar or zip) can be used, and whole-archive compression can also be performed.
     *
     * @param int
     * @param int
     * @param string
     * @return Phar
     **/
    function convertToExecutable($format, $compression, $extension) {}

    /**
     * Copy a file internal to the tar/zip archive to another new file within the same archive.
     * This is an object-oriented alternative to using copy with
     * the phar stream wrapper.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function copy($oldfile, $newfile) {}

    /**
     * For tar-based archives, this method decompresses the entire archive.
     *
     * @param string
     * @return object
     **/
    function decompress($extension) {}

    /**
     * For tar-based archives, this method throws a
     * BadMethodCallException, as compression of individual
     * files within a tar archive is not supported by the file format. Use
     * PharData::compress to compress an entire tar-based archive.
     *
     * @return bool
     **/
    function decompressFiles() {}

    /**
     * Deletes the global metadata of the zip archive
     *
     * @return int
     **/
    function delMetadata() {}

    /**
     * Delete a file within an archive. This is the functional equivalent of
     * calling unlink on the stream wrapper equivalent,
     * as shown in the example below.
     *
     * @param string
     * @return int
     **/
    function delete($entry) {}

    /**
     * Extract all files within a tar/zip archive to disk. Extracted files and directories preserve
     * permissions as stored in the archive. The optional parameters allow optional control over
     * which files are extracted, and whether existing files on disk can be overwritten.
     * The second parameter files can be either the name of a file or
     * directory to extract, or an array of names of files and directories to extract. By
     * default, this method will not overwrite existing files, the third parameter can be
     * set to true to enable overwriting of files.
     * This method is similar to ZipArchive::extractTo.
     *
     * @param string
     * @param string|array
     * @param bool
     * @return int
     **/
    function extractTo($pathto, $files, $overwrite) {}

    /**
     * This method returns if the tar/zip archive on disk is not read-only.
     * Unlike Phar::isWritable, data-only tar/zip archives
     * can be modified even if phar.readonly is set to 1.
     *
     * @return bool
     **/
    function isWritable() {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a tar/zip archive using
     * array access brackets. offsetSet is used for modifying an
     * existing file, or adding a new file to a tar/zip archive.
     *
     * @param string
     * @param string
     * @return void
     **/
    function offsetSet($offset, $value) {}

    /**
     * This is an implementation of the ArrayAccess interface allowing
     * direct manipulation of the contents of a tar/zip archive using
     * array access brackets. offsetUnset is used for deleting an
     * existing file, and is called by the unset
     * language construct.
     *
     * @param string
     * @return bool
     **/
    function offsetUnset($offset) {}

    /**
     * Non-executable tar/zip archives cannot have an alias, so this method simply
     * throws an exception.
     *
     * @param string
     * @return bool
     **/
    function setAlias($alias) {}

    /**
     * Non-executable tar/zip archives cannot have a stub, so this method simply
     * throws an exception.
     *
     * @param string
     * @param string
     * @return void
     **/
    function setDefaultStub($index, $webindex) {}

    /**
     * Non-executable tar/zip archives cannot have a stub, so this method simply
     * throws an exception.
     *
     * @param string
     * @return void
     **/
    function setStub($stub) {}

}
class PharException extends Exception {
}
class PharFileInfo extends SplFileInfo {
    /**
     * PharFileInfo::chmod allows setting of the executable
     * file permissions bit, as well as read-only bits. Writeable bits are
     * ignored, and set at runtime based on the
     * phar.readonly INI variable.
     * As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed if the file is within a Phar
     * archive. Files within PharData archives do not have
     * this restriction.
     *
     * @param int
     * @return void
     **/
    function chmod($permissions) {}

    /**
     * This method compresses the file inside the Phar archive using either bzip2 compression
     * or zlib compression.
     * The bzip2 or zlib
     * extension must be enabled to take
     * advantage of this feature. In addition, if the file is already compressed,
     * the respective extension must be enabled in order
     * to decompress the file. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed if the file is within a Phar
     * archive. Files within PharData archives do not have
     * this restriction.
     *
     * @param int
     * @return bool
     **/
    function compress($compression) {}

    /**
     * This should not be called directly. Instead, a PharFileInfo object
     * is initialized by calling Phar::offsetGet
     * through array access.
     *
     * @param string
     * @return void
     **/
    function __construct($entry) {}

    /**
     * This method decompresses the file inside the Phar archive.
     * Depending on how the file is compressed, the bzip2
     * or zlib extensions must be enabled to take
     * advantage of this feature. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed if the file is within a Phar
     * archive. Files within PharData archives do not have
     * this restriction.
     *
     * @return bool
     **/
    function decompress() {}

    /**
     * Deletes the metadata of the entry, if any.
     *
     * @return bool
     **/
    function delMetadata() {}

    /**
     * This returns the crc32 checksum of the file
     * within the Phar archive.
     *
     * @return int
     **/
    function getCRC32() {}

    /**
     * This returns the size of the file within the Phar archive. Uncompressed files will return
     * the same value for getCompressedSize as they will with filesize
     *
     * @return int
     **/
    function getCompressedSize() {}

    /**
     * Return meta-data that was saved in the Phar archive's manifest for this file.
     *
     * @return int
     **/
    function getMetaData() {}

    /**
     * This returns the flags set in the manifest for a Phar. This will always
     * return 0 in the current implementation.
     *
     * @return int
     **/
    function getPharFlags() {}

    /**
     * Returns the metadata of a file within a phar archive.
     *
     * @return int
     **/
    function hasMetadata() {}

    /**
     * This returns whether a file within a Phar archive
     * has had its CRC verified.
     *
     * @return bool
     **/
    function isCRCChecked() {}

    /**
     * This returns whether a file is compressed within a Phar archive
     * with either Gzip or Bzip2 compression.
     *
     * @return bool
     **/
    function isCompressed() {}

    /**
     * This returns whether a file is compressed within a Phar archive
     * with Bzip2 compression.
     *
     * @return bool
     **/
    function isCompressedBZIP2() {}

    /**
     * This returns whether a file is compressed within a Phar archive
     * with Gzip compression.
     *
     * @return bool
     **/
    function isCompressedGZ() {}

    /**
     * This method compresses the file inside the Phar archive using bzip2 compression.
     * The bzip2 extension must be enabled to take
     * advantage of this feature. In addition, if the file is already compressed using
     * gzip compression, the zlib extension must be enabled in order
     * to decompress the file. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed.
     *
     * @return bool
     **/
    function setCompressedBZIP2() {}

    /**
     * This method compresses the file inside the Phar archive using gzip compression.
     * The zlib extension must be enabled to take
     * advantage of this feature. In addition, if the file is already compressed using
     * bzip2 compression, the bzip2 extension must be enabled in order
     * to decompress the file. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed.
     *
     * @return bool
     **/
    function setCompressedGZ() {}

    /**
     * setMetaData should only be used to store customized data in a file
     * that cannot be represented with existing information stored with a file.
     * Meta-data can significantly slow down the performance of loading a phar
     * archive if the data is large, or if there are many files containing meta-data.
     * It is important to note that file permissions are natively supported inside a
     * phar; it is possible to set them with the
     * PharFileInfo::chmod method. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed if the file is within a Phar
     * archive. Files within PharData archives do not have
     * this restriction.
     *
     * @param mixed
     * @return void
     **/
    function setMetaData($metadata) {}

    /**
     * This method decompresses the file inside the Phar archive.
     * Depending on how the file is compressed, the bzip2
     * or zlib extensions must be enabled to take
     * advantage of this feature. As with all functionality that modifies the contents of
     * a phar, the phar.readonly INI variable
     * must be off in order to succeed.
     *
     * @return bool
     **/
    function setUncompressed() {}

}
class Rar {
    /**
     * Rar::extract extracts entry's data to the
     * dir. It will create new file in the specified
     * dir with the name identical to the entry's name.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function extract($dir, $filepath) {}

    /**
     * Rar::getAttr returns attributes of the archive
     * entry.
     *
     * @return int
     **/
    function getAttr() {}

    /**
     * Rar::getCrc returns CRC of the archive entry.
     *
     * @return int
     **/
    function getCrc() {}

    /**
     * Gets entry last modification time.
     *
     * @return string
     **/
    function getFileTime() {}

    /**
     * Rar::getHostOs return code of the host OS of the
     * archive entry.
     *
     * @return int
     **/
    function getHostOs() {}

    /**
     * Rar::getMethod returns number of the method used when adding
     * current archive entry.
     *
     * @return int
     **/
    function getMethod() {}

    /**
     * Rar::getName returns full name of the archive entry.
     *
     * @return string
     **/
    function getName() {}

    /**
     * Get packed size of the archive entry.
     *
     * @return int
     **/
    function getPackedSize() {}

    /**
     * Get unpacked size of the archive entry.
     *
     * @return int
     **/
    function getUnpackedSize() {}

    /**
     * Get version of the archiver used to add the archive entry.
     *
     * @return int
     **/
    function getVersion() {}

}
class Runkit_Sandbox_Parent {
    /**
     * Instantiating the Runkit_Sandbox_Parent
     * class from within a sandbox environment created from the
     * Runkit_Sandbox class provides some
     * (controlled) means for a sandbox child to access its parent.
     *
     * @return void
     **/
    function __construct() {}

}
class SAMConnection {
    /**
     * Calling the "commit" method on a Connection object commits (completes) all
     * in-flight transactions that are part of the current unit of work.
     *
     * @return bool
     **/
    function commit() {}

    /**
     * Calling the "connect" method on a SAMConnection object connects the PHP
     * script to a messaging server. No messages can be sent or received until a
     * connection is made.
     *
     * @param string
     * @param array
     * @return bool
     **/
    function connect($protocol, $properties) {}

    /**
     * Calling the "disconnect" method on a SAMConnection object disconnects the
     * PHP script from a messaging server. No messages can be sent or received
     * after a connection has been disconnected.
     *
     * @return bool
     **/
    function disconnect() {}

    /**
     * Calling the "isConnected" method on a Connection object will check whether
     * the PHP script is connected to a messaging server. No messages can be sent
     * or received unless a connection has been established with a Messaging
     * server.
     *
     * @return bool
     **/
    function isConnected() {}

    /**
     * @param string
     * @param array
     * @return SAMMessage
     **/
    function peek($target, $properties) {}

    /**
     * @param string
     * @param array
     * @return array
     **/
    function peekAll($target, $properties) {}

    /**
     * @param string
     * @param array
     * @return SAMMessage
     **/
    function receive($target, $properties) {}

    /**
     * Removes a message from a queue.
     *
     * @param string
     * @param array
     * @return SAMMessage
     **/
    function remove($target, $properties) {}

    /**
     * Rolls back an in-flight unit of work.
     *
     * @return bool
     **/
    function rollback() {}

    /**
     * The "send" method is used to send a message to a specific queue or to
     * publish to a specific topic. The method returns a correlation id that can
     * be used as a selector to identify reply or response messages when these
     * are requested.
     *
     * @param string
     * @param SAMMessage
     * @param array
     * @return string
     **/
    function send($target, $msg, $properties) {}

    /**
     * The "subscribe" method is used to create a new subscription to a specified topic.
     *
     * @param string
     * @return string
     **/
    function subscribe($targetTopic) {}

    /**
     * The "unsubscribe" method is used to delete an existing subscription to a
     * specified topic.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function unsubscribe($subscriptionId, $targetTopic) {}

}
class SCA_LocalProxy {
    /**
     * This method is used inside either an ordinary PHP script or an SCA
     * component that needs to create an SDO to pass to a local service. The
     * parameters are the desired SDO's namespace URI and type name. The
     * namespace and type must be defined in the interface of the component
     * that is to be called, so the namespace and type must be defined in one of
     * the schema files which are specfied on the @types annotation within
     * the component for which the SCA_LocalProxy object is a proxy.
     *
     * @param string
     * @param string
     * @return SDO_DataObject
     **/
    function createDataObject($type_namespace_uri, $type_name) {}

}
class SCA_SoapProxy {
    /**
     * This method is used inside either an ordinary PHP script or an SCA
     * component that needs to create an SDO to pass to a web service. The
     * parameters are the desired SDO's namespace URI and type name. The
     * namespace and type must be defined in the interface of the component
     * that is to be called, so the namespace and type must be defined within
     * the WSDL for the web service. If the web service is also an SCA component
     * then the types will have been defined within one of the schema files
     * which are specfied on the @types annotation within the component for
     * which the SCA_SoapProxy object is a proxy.
     *
     * @param string
     * @param string
     * @return SDO_DataObject
     **/
    function createDataObject($type_namespace_uri, $type_name) {}

}
class SCA {
    /**
     * This method is used inside an SCA component that needs to create
     * an SDO to return. The parameters are the desired SDO's namespace URI
     * and type name. The namespace and type must be defined in one of the
     * schema files which are specfied on the @types annotation within the
     * component.
     *
     * @param string
     * @param string
     * @return SDO_DataObject
     **/
    function createDataObject($type_namespace_uri, $type_name) {}

    /**
     * Examine the target and initialise and return a proxy of the appropriate 
     * sort. If the target is for a local PHP component the returned proxy will be an 
     * SCA_LocalProxy. If the target is for a WSDL file, the returned proxy will be a 
     * SCA_SoapProxy.
     *
     * @param string
     * @param string
     * @param array
     * @return mixed
     **/
    function getService($target, $binding, $config) {}

}
class SDO_DAS_ChangeSummary {
    const NONE = 0;
    const MODIFICATION = 0;
    const ADDITION = 0;
    const DELETION = 0;
    /**
     * Begin logging changes made to the SDO_DataObject.
     *
     * @return void
     **/
    function beginLogging() {}

    /**
     * End logging changes made to an SDO_DataObject.
     *
     * @return void
     **/
    function endLogging() {}

    /**
     * Get the type of change which has been made to the supplied SDO_DataObject.
     *
     * @param SDO_DataObject
     * @return int
     **/
    function getChangeType($dataObject) {}

    /**
     * Get an SDO_List of the SDO_DataObjects which have been changed.
     * These data objects can then be used to identify the types 
     * of change made to each, along with the old values.
     *
     * @return SDO_List
     **/
    function getChangedDataObjects() {}

    /**
     * Get the old container (SDO_DataObject) for a deleted SDO_DataObject.
     *
     * @param SDO_DataObject
     * @return SDO_DataObject
     **/
    function getOldContainer($data_object) {}

    /**
     * Get a list of the old values for a given changed SDO_DataObject.
     * Returns a list of SDO_DAS_Settings describing the old values for 
     * the changed properties of the SDO_DataObject.
     *
     * @param SDO_DataObject
     * @return SDO_List
     **/
    function getOldValues($data_object) {}

    /**
     * Test to see whether change logging is switched on.
     *
     * @return bool
     **/
    function isLogging() {}

}
class SDO_DAS_DataFactory {
    /**
     * Adds a property to a type. The type must already be known to the
     * SDO_DAS_DataFactory (i.e. have been added using addType()). The property
     * becomes a property of the type. This is how the graph model for the
     * structure of an SDO_DataObject is built.
     *
     * @param string
     * @param string
     * @param string
     * @param string
     * @param string
     * @param array
     * @return void
     **/
    function addPropertyToType($parent_type_namespace_uri, $parent_type_name, $property_name, $type_namespace_uri, $type_name, $options) {}

    /**
     * Add a new type to the SDO_DAS_DataFactory, 
     * defined by its namespace and type name.
     * The type becomes part of the model of data objects 
     * that the data factory can create.
     *
     * @param string
     * @param string
     * @param array
     * @return void
     **/
    function addType($type_namespace_uri, $type_name, $options) {}

    /**
     * Static method to get an instance of an SDO_DAS_DataFactory. 
     * This instance is initially only configured with the basic SDO types. 
     * A Data Access Service is responsible for populating
     * the data factory model and then allowing PHP applications 
     * to create SDOs based on the model through the SDO_DataFactory interface.
     * PHP applications should always obtain a data factory from a 
     * configured Data Access Service, not through this interface.
     *
     * @return SDO_DAS_DataFactory
     **/
    function getDataFactory() {}

}
class SDO_DAS_DataObject {
    /**
     * Get the SDO_DAS_ChangeSummary for an SDO_DAS_DataObject, 
     * or NULL if it does not have one.
     *
     * @return SDO_DAS_ChangeSummary
     **/
    function getChangeSummary() {}

}
class SDO_DAS_Setting {
    /**
     * Get the list index for a modification made to an element of a 
     * many-valued property. 
     * For example, if we modified the third element of a 
     * many-valued property
     * we could obtain an SDO_DAS_Setting from the 
     * change summary corresponding to that modification.
     * A call to
     * getListIndex
     * on that setting would return the value 2 (lists are indexed from zero).
     *
     * @return int
     **/
    function getListIndex() {}

    /**
     * Returns the property index for the changed property. 
     * This index identifies the property which was modified in data object.
     *
     * @return int
     **/
    function getPropertyIndex() {}

    /**
     * Returns the property name for the changed property. 
     * This name identifies the property which was modified in data object.
     *
     * @return string
     **/
    function getPropertyName() {}

    /**
     * Returns the old value for the changed property.
     * This can be used by a Data Access Service when 
     * writing updates to a data source.
     * The DAS uses the old value to detect conflicts by comparing 
     * it with the current value in the data source.
     * If they do not match, then the data source has been updated 
     * since the data object was originally populated, and therefore
     * writing any new updates risks compromising the integrity of the data.
     *
     * @return mixed
     **/
    function getValue() {}

}
class SDO_DataFactory {
    /**
     * Create a new SDO_DataObject given the data object's 
     * namespace URI and type name.
     *
     * @param string
     * @param string
     * @return void
     **/
    function create($type_namespace_uri, $type_name) {}

}
class SDO_DataObject {
    /**
     * Clear an SDO_DataObject's properties. 
     * Read-only properties are unaffected.
     * Subsequent calls to isset() for the data object will return .
     *
     * @return void
     **/
    function clear() {}

    /**
     * Create a child SDO_DataObject of the default type for the 
     * property identified.
     * The data object is automatically inserted into the tree 
     * and a reference to it is returned.
     *
     * @param mixed
     * @return SDO_DataObject
     **/
    function createDataObject($identifier) {}

    /**
     * Get the data object which contains this data object.
     *
     * @return SDO_DataObject
     **/
    function getContainer() {}

    /**
     * Return the SDO_Sequence for this SDO_DataObject. 
     * Accessing the SDO_DataObject through the SDO_Sequence interface 
     * acts on the same SDO_DataObject instance data, 
     * but preserves ordering across properties.
     *
     * @return SDO_Sequence
     **/
    function getSequence() {}

    /**
     * Return the name of the type for a data object.
     * A convenience method corresponding to 
     * SDO_Model_ReflectionDataObject::getType().getName().
     *
     * @return string
     **/
    function getTypeName() {}

    /**
     * Return the namespace URI of the type for a data object.
     * A convenience method corresponding to 
     * SDO_Model_ReflectionDataObject::getType().getNamespaceURI().
     *
     * @return string
     **/
    function getTypeNamespaceURI() {}

}
class SDO_Exception {
    /**
     * Returns the cause of this exception or NULL if the cause is nonexistent or unknown.
     * Typically the cause will be an SDO_CPPException object, which may
     * be used to obtain additional diagnostic information.
     *
     * @return mixed
     **/
    function getCause() {}

}
class SDO_List {
    /**
     * Insert a new element at a specified position in the list.
     * All subsequent list items are moved up.
     *
     * @param mixed
     * @param int
     * @return void
     **/
    function insert($value, $index) {}

}
class SDO_Model_Property {
    /**
     * Returns the SDO_Model_Type which contains this property.
     *
     * @return SDO_Model_Type
     **/
    function getContainingType() {}

    /**
     * Returns the default value for the property.
     * Only primitive data type properties can have default values.
     *
     * @return mixed
     **/
    function getDefault() {}

    /**
     * Returns the name of the SDO_Model_Property.
     *
     * @return string
     **/
    function getName() {}

    /**
     * Get the SDO_Model_Type of the property.
     * The SDO_Model_Type describes the type information for the property, such 
     * as its type name, namespace URI, whether it is a primitive data type, 
     * and so on.
     *
     * @return SDO_Model_Type
     **/
    function getType() {}

    /**
     * Test to see if the property corresponds to a containment relationship.
     * Returns if the property defines a containment relationship,
     * or if it is reference.
     *
     * @return bool
     **/
    function isContainment() {}

    /**
     * Test to see if the property is many-valued. 
     * Returns if this is a many-valued property, otherwise returns 
     * .
     *
     * @return bool
     **/
    function isMany() {}

}
class SDO_Model_ReflectionDataObject {
    /**
     * Construct an SDO_Model_ReflectionDataObject to reflect on an 
     * SDO_DataObject. Reflecting on an SDO_DataObject gives access to 
     * information about its model. The model contains information such as 
     * the data object's type, and whether that type is sequenced
     * (preserves ordering across properties) or open (each instance can have 
     * its model extended). The model also holds information about the data 
     * object's properties, any default values they may have, and so on.
     *
     * @param SDO_DataObject
     * @return SDO_Model_ReflectionDataObject
     **/
    function __construct($data_object) {}

    /**
     * Get a string describing the SDO_DataObject.
     * The default behaviour is to print the output, but
     * if is specified for return, it is returned as a string.
     *
     * @param SDO_Model_ReflectionDataObject
     * @param bool
     * @return mixed
     **/
    function export($rdo, $return) {}

    /**
     * Get the SDO_Model_Property that contains the SDO_DataObject. 
     * This method is used to navigate up to the parent's property which 
     * contains the data object which has been reflected upon.
     *
     * @return SDO_Model_Property
     **/
    function getContainmentProperty() {}

    /**
     * Get the instance properties for the SDO_DataObject. The instance 
     * properties consist of all the properties defined on the data object's 
     * type, plus any instance properties from open content (if the data object
     * is an open type).
     *
     * @return array
     **/
    function getInstanceProperties() {}

    /**
     * Returns the SDO_Model_Type for the SDO_DataObject. The SDO_Model_Type
     * holds all the information about the data object's type, such as namespace 
     * URI, type name, whether it is a primitive data type, and so on.
     *
     * @return SDO_Model_Type
     **/
    function getType() {}

}
class SDO_Model_Type {
    /**
     * Get the base type for this type.
     * Returns the SDO_Model_Type for the base type if this type inherits from 
     * another, otherwise returns . An example of when base types occur 
     * is when a type defined in XML schema inherits from another type by using 
     * .
     *
     * @return SDO_Model_Type
     **/
    function getBaseType() {}

    /**
     * Returns the name of the type. The combination of type name and namespace 
     * URI is used to uniquely identify the type.
     *
     * @return string
     **/
    function getName() {}

    /**
     * Returns the namespace URI of the type. The combination of namespace URI 
     * and type name is used to uniquely identify the type.
     *
     * @return string
     **/
    function getNamespaceURI() {}

    /**
     * Get an array of SDO_Model_Property objects describing the properties 
     * defined for the SDO_Model_Type. Each SDO_Model_Property holds 
     * information such as the property name, default value, and so on.
     *
     * @return array
     **/
    function getProperties() {}

    /**
     * Get an SDO_Model_Property of the type, identified by its property index 
     * or property name.
     *
     * @param mixed
     * @return SDO_Model_Property
     **/
    function getProperty($identifier) {}

    /**
     * Test to see if this SDO_Model_Type is an abstract data type.
     * Returns if this type is abstract, that is, no SDO_DataObject
     * of this type can be instantiated, though other types may inherit
     * from it.
     *
     * @return bool
     **/
    function isAbstractType() {}

    /**
     * Test to see if this SDO_Model_Type is a primitive data type.
     * Returns if this type is a primitive data type, otherwise returns 
     * .
     *
     * @return bool
     **/
    function isDataType() {}

    /**
     * Test for an SDO_DataObject being an instance of this SDO_Model_Type.
     * Returns if the SDO_DataObject provided is an instance of this 
     * SDO_Model_Type, or a derived type, otherwise returns .
     *
     * @param SDO_DataObject
     * @return bool
     **/
    function isInstance($data_object) {}

    /**
     * Test to see if this type is open.
     * Returns if this type is open, otherwise returns . An 
     * SDO_DataObject whose type is open can have properties added to them which 
     * are not described by the type. This capability is used to support 
     * working with XML documents whose schema support open content, such as that 
     * defined by an element.
     *
     * @return bool
     **/
    function isOpenType() {}

    /**
     * Test to see if this is a sequenced type. Returns if this type is 
     * sequence, otherwise returns .
     * Sequenced types can have the ordering across properties preserved and can 
     * contain unstructured text. For more information on sequenced types see 
     * the section on 
     * Working with Sequenced Data
     * Objects.
     *
     * @return bool
     **/
    function isSequencedType() {}

}
class SDO_Sequence {
    /**
     * Return the property for the specified sequence index.
     *
     * @param int
     * @return SDO_Model_Property
     **/
    function getProperty($sequence_index) {}

    /**
     * Insert a new element at a specified position in the sequence. 
     * All subsequent sequence items are moved up.
     *
     * @param mixed
     * @param int
     * @param mixed
     * @return void
     **/
    function insert($value, $sequenceIndex, $propertyIdentifier) {}

    /**
     * Modify the position of the item in the sequence, 
     * without altering the value of the property in the SDO_DataObject.
     *
     * @param int
     * @param int
     * @return void
     **/
    function move($toIndex, $fromIndex) {}

}
class SDO_DAS_XML_Document {
    /**
     * Returns the root SDO_DataObject.
     *
     * @return SDO_DataObject
     **/
    function getRootDataObject() {}

    /**
     * Returns root element's name.
     *
     * @return string
     **/
    function getRootElementName() {}

    /**
     * Returns root element's URI string.
     *
     * @return string
     **/
    function getRootElementURI() {}

    /**
     * Sets the given string as encoding.
     *
     * @param string
     * @return void
     **/
    function setEncoding($encoding) {}

    /**
     * Controls whether an XML declaration will be generated at the start of the 
     * XML document. Set to true to generate the XML declaration,
     * or false to suppress it.
     *
     * @param bool
     * @return void
     **/
    function setXMLDeclaration($xmlDeclatation) {}

    /**
     * Sets the given string as xml version.
     *
     * @param string
     * @return void
     **/
    function setXMLVersion($xmlVersion) {}

}
class SDO_DAS_XML {
    /**
     * Load a second or subsequent schema file to an XML DAS that has already
     * been created with the static method create.
     * Although the file may be any valid schema file, a likely reason for 
     * using this method is to add a schema file containing definitions of 
     * extra complex types, hence the name. See Example 4 of the parent document 
     * for an example.
     *
     * @param string
     * @return void
     **/
    function addTypes($xsd_file) {}

    /**
     * This is the only static method of SDO_DAS_XML class. 
     * Used to instantiate SDO_DAS_XML object.
     *
     * @param mixed
     * @param string
     * @return SDO_DAS_XML
     **/
    function create($xsd_file, $key) {}

    /**
     * Creates SDO_DataObject for a given namespace URI and type name. 
     * The type should be defined in the underlying model 
     * otherwise SDO_TypeNotFoundException will be thrown.
     *
     * @param string
     * @param string
     * @return SDO_DataObject
     **/
    function createDataObject($namespace_uri, $type_name) {}

    /**
     * Creates an XML Document object. This will contain just one empty root element
     * on which none of the properties will have been set.
     * The purpose of this call is to allow an application to create 
     * an XML document from scratch without the need to load a 
     * document from a file or string. The document that is created 
     * will be as if a document had been loaded that contained just a single
     * empty document element with no attributes set or elements within it.
     *
     * @param string
     * @return SDO_DAS_XML_Document
     **/
    function createDocument($document_element_name) {}

    /**
     * Constructs the tree of SDO_DataObjects from the given address 
     * to xml instance document. 
     * Returns SDO_DAS_XML_Document Object. 
     * Use SDO_DAS_XML_Document::getRootDataObject 
     * method to get root data object.
     *
     * @param string
     * @return SDO_XMLDocument
     **/
    function loadFile($xml_file) {}

    /**
     * Constructs the tree of SDO_DataObjects from the given xml instance string. 
     * Returns SDO_DAS_XML_Document Object. 
     * Use SDO_DAS_XML_Document::getRootDataObject method to get root data object.
     *
     * @param string
     * @return SDO_DAS_XML_Document
     **/
    function loadString($xml_string) {}

    /**
     * Saves the SDO_DAS_XML_Document object to a file.
     *
     * @param SDO_XMLDocument
     * @param string
     * @param int
     * @return void
     **/
    function saveFile($xdoc, $xml_file, $indent) {}

    /**
     * Saves the SDO_DAS_XML_Document object to string.
     *
     * @param SDO_XMLDocument
     * @param int
     * @return string
     **/
    function saveString($xdoc, $indent) {}

}
class SDO_DAS_Relational {
    /**
     * Given a PDO database handle and the special root object of a data graph, 
     * examine the change summary in the datagraph and applies the changes 
     * to the database.
     * The changes that it can apply can be creations of data objects, 
     * deletes of data objects, and modifications to properties of data objects.
     *
     * @param PDO
     * @param SDODataObject
     * @return void
     **/
    function applyChanges($database_handle, $root_data_object) {}

    /**
     * Constructs an instance of a Relational Data Access Service 
     * from the passed metadata.
     *
     * @param array
     * @param string
     * @param array
     * @return SDO_DAS_Relational
     **/
    function __construct($database_metadata, $application_root_type, $SDO_containment_references_metadata) {}

    /**
     * Returns the special root object at the top of an otherwise 
     * empty data graph.
     * This call is used when the application wants to create a 
     * data graph from scratch, without having called
     * executeQuery
     * to create a data graph.
     *
     * @return SDODataObject
     **/
    function createRootDataObject() {}

    /**
     * Executes a given query against the relational database, 
     * using the supplied PDO database handle.
     * Differs from the simpler 
     * executeQuery
     * in that it takes a prepared statement and a list of values.
     * This is the appropriate call to use either when the statement is 
     * to executed a number of times with different arguments, and there
     * is therefore a performance benefit to be had from preparing the 
     * statement only once, or when the the SQL statement is to contain 
     * varying values taken from a source that cannot be completely trusted.
     * In this latter case it may be unsafe to construct the SQL statement
     * by simply concatenating the parts of the statement together, 
     * since the values may contain pieces of SQL. 
     * To guard against this, a so-called SQL injection attack,
     * it is safer to prepare the SQL statement with placeholders 
     * (also known as parameter markers, denoted by '?') and supply a 
     * list of the values to be substituted as a separate argument. 
     * Otherwise this function is the same as 
     * executeQuery in that 
     * it uses the model that it built from the the metadata 
     * to interpret the result set and returns a data graph.
     *
     * @param PDO
     * @param PDOStatement
     * @param array
     * @param array
     * @return SDODataObject
     **/
    function executePreparedQuery($database_handle, $prepared_statement, $value_list, $column_specifier) {}

    /**
     * Executes a given query against the relational database, 
     * using the supplied PDO database handle.
     * Uses the model that it built from the the metadata 
     * to interpret the result set.
     * Returns a data graph.
     *
     * @param PDO
     * @param string
     * @param array
     * @return SDODataObject
     **/
    function executeQuery($database_handle, $SQL_statement, $column_specifier) {}

}
class SimpleXMLElement {
    /**
     * Adds an attribute to the SimpleXML element.
     *
     * @param string
     * @param string
     * @param string
     * @return void
     **/
    function addAttribute($name, $value, $namespace) {}

    /**
     * Adds a child element to the node and returns a SimpleXMLElement of the child.
     *
     * @param string
     * @param string
     * @param string
     * @return SimpleXMLElement
     **/
    function addChild($name, $value, $namespace) {}

    /**
     * The asXML method formats the parent object's data
     * in XML version 1.0.
     *
     * @param string
     * @return mixed
     **/
    function asXML($filename) {}

    /**
     * This function provides the attributes and values defined within an xml tag.
     *
     * @param string
     * @param bool
     * @return SimpleXMLElement
     **/
    function attributes($ns, $is_prefix) {}

    /**
     * This method finds the children of the element of which it is a member. The result
     * follows normal iteration rules.
     *
     * @param string
     * @param bool
     * @return SimpleXMLElement
     **/
    function children($ns, $is_prefix) {}

    /**
     * Returns namespaces declared in document
     *
     * @param bool
     * @return array
     **/
    function getDocNamespaces($recursive) {}

    /**
     * Gets the name of the XML element.
     *
     * @return string
     **/
    function getName() {}

    /**
     * Returns namespaces used in document
     *
     * @param bool
     * @return array
     **/
    function getNamespaces($recursive) {}

    /**
     * Creates a prefix/ns context for the next XPath query. In particular, this is
     * helpful if the provider of the given XML document alters the namespace
     * prefixes. registerXPathNamespace will create a prefix for
     * the associated namespace, allowing one to access nodes in that namespace 
     * without the need to change code to allow for the new prefixes dictated by the
     * provider.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function registerXPathNamespace($prefix, $ns) {}

    /**
     * The xpath method searches the SimpleXML node for
     * children matching the XPath path.
     *
     * @param string
     * @return array
     **/
    function xpath($path) {}

}
class SoapClient {
    /**
     * This method is deprecated. Use instead of it.
     *
     * @param string
     * @param array
     * @param array
     * @param array
     * @param array
     * @return mixed
     **/
    function __call($function_name, $arguments, $options, $input_headers, $output_headers) {}

    /**
     * Performs SOAP request over HTTP.
     *
     * @param string
     * @param string
     * @param string
     * @param int
     * @param int
     * @return string
     **/
    function __doRequest($request, $location, $action, $version, $one_way) {}

    /**
     * Returns the list of SOAP functions.
     *
     * @return array
     **/
    function __getFunctions() {}

    /**
     * @return string
     **/
    function __getLastRequest() {}

    /**
     * @return string
     **/
    function __getLastRequestHeaders() {}

    /**
     * @return string
     **/
    function __getLastResponse() {}

    /**
     * @return string
     **/
    function __getLastResponseHeaders() {}

    /**
     * This function works only in WSDL mode.
     *
     * @return array
     **/
    function __getTypes() {}

    /**
     * Defines a cookie to be sent along with the SOAP requests.
     *
     * @param string
     * @param string
     * @return void
     **/
    function __setCookie($name, $value) {}

    /**
     * This is a low level API function that is used to make a SOAP call. Usually,
     * in WSDL mode,
     * you can simply call SOAP functions as SoapClient 
     * methods. This method useful in non-WSDL mode when soapaction 
     * is unknown, uri differs from the default or when sending
     * and/or receiving SOAP Headers.
     *
     * @param string
     * @param array
     * @param array
     * @param mixed
     * @param array
     * @return mixed
     **/
    function __soapCall($function_name, $arguments, $options, $input_headers, $output_headers) {}

}
class SoapServer {
    /**
     * Exports one or more functions for remote clients.
     *
     * @param mixed
     * @return void
     **/
    function addFunction($functions) {}

    /**
     * @param string
     * @param string
     * @param string
     * @param mixed
     * @param string
     * @return void
     **/
    function fault($code, $string, $actor, $details, $name) {}

    /**
     * This method returns the list of all functions added by 
     * or 
     * .
     *
     * @return array
     **/
    function getFunctions() {}

    /**
     * Processes a SOAP request, calls necessary functions, and sends a response 
     * back.
     *
     * @param string
     * @return void
     **/
    function handle($soap_request) {}

    /**
     * Exports all methods from specified class.
     *
     * @param string
     * @param mixed
     * @return void
     **/
    function setClass($class_name, $args) {}

    /**
     * This function allows saving data between requests in a PHP session. It works only
     * with a server that exports functions from a class with
     * .
     *
     * @param int
     * @return void
     **/
    function setPersistence($mode) {}

}
class SphinxClient {
    /**
     * Adds query with the current settings to multi-query batch. This method
     * doesn't affect current settings (sorting, filtering, grouping etc.) in any way.
     *
     * @param string
     * @param string
     * @param string
     * @return int
     **/
    function addQuery($query, $index, $comment) {}

    /**
     * Connects to searchd, requests it to generate excerpts (snippets) from the
     * given documents, and returns the results.
     *
     * @param array
     * @param string
     * @param string
     * @param array
     * @return array
     **/
    function buildExcerpts($docs, $index, $words, $opts) {}

    /**
     * Extracts keywords from query using tokenizer 
     * settings for the given index, optionally with
     * per-keyword occurrence statistics.
     *
     * @param string
     * @param string
     * @param bool
     * @return array
     **/
    function buildKeywords($query, $index, $hits) {}

    /**
     * Creates a new SphinxClient object.
     *
     **/
    function __construct() {}

    /**
     * Escapes characters that are treated as special operators by the query
     * language parser.
     *
     * @param string
     * @return string
     **/
    function escapeString($string) {}

    /**
     * Returns string with the last error message. If there were no errors during
     * the previous API call, empty string is returned. This method doesn't reset
     * the error message, so you can safely call it several times.
     *
     * @return string
     **/
    function getLastError() {}

    /**
     * Returns last warning message. If there were no warnings during 
     * the previous API call, empty string is returned. This method doesn't reset
     * the warning, so you can safely call it several times.
     *
     * @return string
     **/
    function getLastWarning() {}

    /**
     * Connects to searchd server, runs the given search query with the current settings,
     * obtains and returns the result set.
     *
     * @param string
     * @param string
     * @param string
     * @return array
     **/
    function query($query, $index, $comment) {}

    /**
     * Clears all currently set filters. This call is normally required when
     * using multi-queries. You might want to set different filters for different
     * queries in the batch. To do that, you should call
     * SphinxClient::resetFilters and add new filters using 
     * the respective calls.
     *
     * @return void
     **/
    function resetFilters() {}

    /**
     * Clears all currently group-by settings, and disables group-by. 
     * This call is normally required only when using multi-queries.
     *
     * @return void
     **/
    function resetGroupBy() {}

    /**
     * Connects to searchd, runs a batch of all queries added using , obtains and returns the result sets.
     *
     * @return array
     **/
    function runQueries() {}

    /**
     * Controls the format of search results set arrays (whether matches should
     * be returned as an array or a hash).
     * If array_result is (default value), matches
     * are returned as a hash with document IDs as keys, and other information (weight,
     * attributes) as values. If array_result is , matches 
     * are eturned as a plain array with complete per-match information including
     * document IDs.
     *
     * @param bool
     * @return bool
     **/
    function setArrayResult($array_result) {}

    /**
     * Sets connection timeout (in seconds) for searchd connection.
     *
     * @param float
     * @return bool
     **/
    function setConnectTimeout($timeout) {}

    /**
     * Binds per-field weights by name.
     *
     * @param array
     * @return bool
     **/
    function setFieldWeights($weights) {}

    /**
     * Adds new integer values set filter to the existing list of filters.
     *
     * @param string
     * @param array
     * @param bool
     * @return bool
     **/
    function setFilter($attribute, $values, $exclude) {}

    /**
     * Adds new float range filter to the existing list of filters.
     * Only those documents which have attribute 
     * value stored in the index between min and
     * max (including values that are exactly equal 
     * to min or max) will 
     * be matched (or rejected, if exclude is ).
     *
     * @param string
     * @param float
     * @param float
     * @param bool
     * @return bool
     **/
    function setFilterFloatRange($attribute, $min, $max, $exclude) {}

    /**
     * Adds new integer range filter to the existing list of filters.
     * Only those documents which have attribute 
     * value stored in the index between min and
     * max (including values that are exactly equal 
     * to min or max) will 
     * be matched (or rejected, if exclude is ).
     *
     * @param string
     * @param int
     * @param int
     * @param bool
     * @return bool
     **/
    function setFilterRange($attribute, $min, $max, $exclude) {}

    /**
     * Sets anchor point for a geosphere distance (geodistance) calculations
     * and enables them.
     *
     * @param string
     * @param string
     * @param float
     * @param float
     * @return bool
     **/
    function setGeoAnchor($attrlat, $attrlong, $latitude, $longitude) {}

    /**
     * Sets grouping attribute, function, and group sorting mode, and enables
     * grouping.
     *
     * @param string
     * @param int
     * @param string
     * @return bool
     **/
    function setGroupBy($attribute, $func, $groupsort) {}

    /**
     * Sets attribute name for per-group distinct values count calculations. Only
     * available for grouping queries. For each group, all values of
     * attribute will be stored, then the amount of
     * distinct values will be calculated and returned to the client. This feature
     * is similar to COUNT(DISTINCT) clause in SQL.
     *
     * @param string
     * @return bool
     **/
    function setGroupDistinct($attribute) {}

    /**
     * Sets an accepted range of document IDs. Default range is from 0 to 0, i.e.
     * no limit. Only those records that have document ID between
     * min and max 
     * (including IDs exactly equal to min or
     * max) will be matched.
     *
     * @param int
     * @param int
     * @return bool
     **/
    function setIDRange($min, $max) {}

    /**
     * Sets per-index weights and enables weighted summing of match weights across
     * different indexes.
     *
     * @param array
     * @return bool
     **/
    function setIndexWeights($weights) {}

    /**
     * Sets offset into server-side result set and amount
     * of matches to return to client starting from that offset
     * (limit). Can additionally control maximum
     * server-side result set size for current query
     * (max_matches) and the threshold amount of matches
     * to stop searching at (cutoff).
     *
     * @param int
     * @param int
     * @param int
     * @param int
     * @return bool
     **/
    function setLimits($offset, $limit, $max, $cutoff) {}

    /**
     * Sets full-text query matching mode. mode is one of
     * the constants listed below.
     * 
     * Match modes
     * 
     * 
     * 
     * Constant
     * Description
     * 
     * 
     * 
     * 
     * SPH_MATCH_ALL
     * Match all query words (default mode).
     * 
     * 
     * SPH_MATCH_ANY
     * Match any of query words.
     * 
     * 
     * SPH_MATCH_PHRASE
     * Match query as a phrase, requiring perfect match.
     * 
     * 
     * SPH_MATCH_BOOLEAN
     * Match query as a boolean expression.
     * 
     * 
     * SPH_MATCH_EXTENDED
     * Match query as an expression in Sphinx internal query language.
     * 
     * 
     * SPH_MATCH_FULLSCAN
     * Enables fullscan.
     * 
     * 
     * SPH_MATCH_EXTENDED2
     * The same as SPH_MATCH_EXTENDED plus ranking
     * and quorum searching support.
     *
     * @param int
     * @return bool
     **/
    function setMatchMode($mode) {}

    /**
     * Sets maximum search query time, in milliseconds. qtime must be a
     * non-negative integer. Default value is 0, i.e. no limit.
     *
     * @param int
     * @return bool
     **/
    function setMaxQueryTime($qtime) {}

    /**
     * Sets ranking mode. Only available in
     * SPH_MATCH_EXTENDED2 matching mode.
     * 
     * Ranking modes
     * 
     * 
     * 
     * Constant
     * Description
     * 
     * 
     * 
     * 
     * SPH_RANK_PROXIMITY_BM25
     * Default ranking mode which uses both proximity and BM25
     * ranking.
     * 
     * 
     * SPH_RANK_BM25
     * Statistical ranking mode which uses BM25 ranking only (similar
     * to most of other full-text engines). This mode is faster, but may result
     * in worse quality on queries which contain more than 1 keyword.
     * 
     * 
     * SPH_RANK_NONE
     * Disables ranking. This mode is the fastest. It is essentially
     * equivalent to boolean searching, a weight of 1 is assigned to all
     * matches.
     *
     * @param int
     * @return bool
     **/
    function setRankingMode($ranker) {}

    /**
     * Sets distributed retry count and delay.
     *
     * @param int
     * @param int
     * @return bool
     **/
    function setRetries($count, $delay) {}

    /**
     * Sets searchd host name and TCP port. All subsequent requests will use the
     * new host and port settings. Default host and port are 'localhost' and 3312,
     * respectively.
     *
     * @param string
     * @param int
     * @return bool
     **/
    function setServer($server, $port) {}

    /**
     * Sets matches sorting mode. See available modes below.
     * 
     * Sorting modes
     * 
     * 
     * 
     * Constant
     * Description
     * 
     * 
     * 
     * 
     * SPH_SORT_RELEVANCE
     * Sort by relevance in descending order (best matches first).
     * 
     * 
     * SPH_SORT_ATTR_DESC
     * Sort by an attribute in descending order (bigger attribute
     * values first).
     * 
     * 
     * SPH_SORT_ATTR_ASC
     * Sort by an attribute in ascending order (smaller attribute
     * values first).
     * 
     * 
     * SPH_SORT_TIME_SEGMENTS
     * Sort by time segments (last hour/day/week/month) in descending
     * order, and then by relevance in descending order.
     * 
     * 
     * SPH_SORT_EXTENDED
     * Sort by SQL-like combination of columns in ASC/DESC order.
     * 
     * 
     * SPH_SORT_EXPR
     * Sort by an arithmetic expression.
     *
     * @param int
     * @param string
     * @return bool
     **/
    function setSortMode($mode, $sortby) {}

    /**
     * Instantly updates given attribute values in given documents.
     *
     * @param string
     * @param array
     * @param array
     * @return int
     **/
    function updateAttributes($index, $attributes, $values) {}

}
class ArrayIterator implements Iterator, Traversable, ArrayAccess, SeekableIterator, Countable {
    /**
     * Get the current array entry.
     *
     * @return mixed
     **/
    function current() {}

    /**
     * This function returns the current array key
     *
     * @return mixed
     **/
    function key() {}

    /**
     * The iterator to the next entry.
     *
     * @return void
     **/
    function next() {}

    /**
     * This rewinds the iterator to the beginning.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * @param int
     * @return void
     **/
    function seek($position) {}

    /**
     * Checks if the array contains any more entries.
     *
     * @return bool
     **/
    function valid() {}

}
class ArrayObject implements IteratorAggregate, Traversable, ArrayAccess, Countable {
    /**
     * @param mixed
     * @return void
     **/
    function append($newval) {}

    /**
     * @return int
     **/
    function count() {}

    /**
     * Create a new iterator from an ArrayObject instance.
     *
     * @return ArrayIterator
     **/
    function getIterator() {}

    /**
     * @param mixed
     * @return bool
     **/
    function offsetExists($index) {}

    /**
     * @param mixed
     * @return mixed
     **/
    function offsetGet($index) {}

    /**
     * Sets the value at the specified index to newval.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function offsetSet($index, $newval) {}

    /**
     * Unsets the value at the specified index.
     *
     * @param mixed
     * @return void
     **/
    function offsetUnset($index) {}

}
class CachingIterator extends IteratorIterator implements OuterIterator, Traversable, Iterator, ArrayAccess, Countable {
    const CALL_TOSTRING = 0;
    const CATCH_GET_CHILD = 0;
    /**
     * @return bool
     **/
    function hasNext() {}

    /**
     * Move the iterator forward.
     *
     * @return void
     **/
    function next() {}

    /**
     * Rewind the iterator.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * Get the string representation of the current element.
     *
     * @return string
     **/
    function __toString() {}

    /**
     * Check whether the current element is valid.
     *
     * @return bool
     **/
    function valid() {}

}
class DirectoryIterator extends SplFileInfo implements Iterator, Traversable {
    /**
     * @return DirectoryIterator
     **/
    function current() {}

    /**
     * Get the last access time of file.
     *
     * @return int
     **/
    function getATime() {}

    /**
     * Get the inode modification time of file.
     *
     * @return int
     **/
    function getCTime() {}

    /**
     * Get the filename of the current dir entry.
     *
     * @return string
     **/
    function getFilename() {}

    /**
     * Get the files group.
     *
     * @return int
     **/
    function getGroup() {}

    /**
     * Get the inode of the file.
     *
     * @return int
     **/
    function getInode() {}

    /**
     * Get the last modification time of the file.
     *
     * @return int
     **/
    function getMTime() {}

    /**
     * Get the owner of the file.
     *
     * @return int
     **/
    function getOwner() {}

    /**
     * Get the directory path.
     *
     * @return string
     **/
    function getPath() {}

    /**
     * Get the path and filename of the current dir entry.
     *
     * @return string
     **/
    function getPathname() {}

    /**
     * Get the permissions of the file.
     *
     * @return int
     **/
    function getPerms() {}

    /**
     * Get the file size.
     *
     * @return int
     **/
    function getSize() {}

    /**
     * Get the file type.
     *
     * @return string
     **/
    function getType() {}

    /**
     * Check if the file is a directory.
     *
     * @return bool
     **/
    function isDir() {}

    /**
     * Check whether it's a directory and either .
     * or ...
     *
     * @return bool
     **/
    function isDot() {}

    /**
     * Checks if the file is executable.
     *
     * @return bool
     **/
    function isExecutable() {}

    /**
     * Checks if it's a regular file.
     *
     * @return bool
     **/
    function isFile() {}

    /**
     * Checks if the entry is a symbolic link.
     *
     * @return bool
     **/
    function isLink() {}

    /**
     * Checks if the entry is readable.
     *
     * @return bool
     **/
    function isReadable() {}

    /**
     * Checks if the entry is writable.
     *
     * @return bool
     **/
    function isWritable() {}

    /**
     * Get the current dir entry.
     *
     * @return string
     **/
    function key() {}

    /**
     * Move to the next entry.
     *
     * @return void
     **/
    function next() {}

    /**
     * Rewind dir back to the start.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * Check whether dir contains more entries.
     *
     * @return string
     **/
    function valid() {}

}
class FilterIterator extends IteratorIterator implements OuterIterator, Traversable, Iterator {
    /**
     * Get the current element value.
     *
     * @return mixed
     **/
    function current() {}

    /**
     * Get the inner iterator.
     *
     * @return Iterator
     **/
    function getInnerIterator() {}

    /**
     * Get the current key.
     *
     * @return mixed
     **/
    function key() {}

    /**
     * Move the iterator forward.
     *
     * @return void
     **/
    function next() {}

    /**
     * Rewind the iterator.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * Checks whether the current element is valid.
     *
     * @return bool
     **/
    function valid() {}

}
class LimitIterator extends IteratorIterator implements OuterIterator, Traversable, Iterator {
    /**
     * @return int
     **/
    function getPosition() {}

    /**
     * Moves the iterator forward.
     *
     * @return void
     **/
    function next() {}

    /**
     * Rewinds the iterator to the specified starting offset.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * @param int
     * @return void
     **/
    function seek($position) {}

    /**
     * Checks whether the current element is valid.
     *
     * @return bool
     **/
    function valid() {}

}
class ParentIterator extends RecursiveFilterIterator implements RecursiveIterator, OuterIterator, Traversable, Iterator {
    /**
     * Get the the inner iterator's children contained in a ParentIterator.
     *
     * @return ParentIterator
     **/
    function getChildren() {}

    /**
     * Check whether the inner iterator's current element has children.
     *
     * @return bool
     **/
    function hasChildren() {}

    /**
     * Moves the iterator forward.
     *
     * @return void
     **/
    function next() {}

    /**
     * Rewinds the iterator.
     *
     * @return void
     **/
    function rewind() {}

}
class RecursiveCachingIterator extends CachingIterator implements Countable, ArrayAccess, Iterator, Traversable, OuterIterator, RecursiveIterator {
    /**
     * @return RecursiveCachingIterator
     **/
    function getChildren() {}

    /**
     * @return boolean
     **/
    function hasChildren() {}

}
class RecursiveDirectoryIterator extends DirectoryIterator implements Traversable, Iterator, RecursiveIterator {
    /**
     * @return object
     **/
    function getChildren() {}

    /**
     * @param bool
     * @return bool
     **/
    function hasChildren($allow_links) {}

    /**
     * @return string
     **/
    function key() {}

    /**
     * @return void
     **/
    function next() {}

    /**
     * @return void
     **/
    function rewind() {}

}
class RecursiveIteratorIterator implements OuterIterator, Traversable, Iterator {
    const LEAVES_ONLY = 0;
    const SELF_FIRST = 0;
    const CHILD_FIRST = 0;
    /**
     * @return mixed
     **/
    function current() {}

    /**
     * @return int
     **/
    function getDepth() {}

    /**
     * @return RecursiveIterator
     **/
    function getSubIterator() {}

    /**
     * @return mixed
     **/
    function key() {}

    /**
     * @return void
     **/
    function next() {}

    /**
     * @return void
     **/
    function rewind() {}

    /**
     * @return boolean
     **/
    function valid() {}

}
class SimpleXMLIterator extends SimpleXMLElement implements RecursiveIterator, Traversable, Iterator, Countable {
    /**
     * @return mixed
     **/
    function current() {}

    /**
     * @return object
     **/
    function getChildren() {}

    /**
     * @return bool
     **/
    function hasChildren() {}

    /**
     * @return mixed
     **/
    function key() {}

    /**
     * @return void
     **/
    function next() {}

    /**
     * @return void
     **/
    function rewind() {}

    /**
     * @return bool
     **/
    function valid() {}

}
class SplDoublyLinkedList implements Iterator, ArrayAccess, Countable {
    /**
     * @return mixed
     **/
    function bottom() {}

    /**
     * @return int
     **/
    function count() {}

    /**
     * Get the current doubly linked list node.
     *
     * @return mixed
     **/
    function current() {}

    /**
     * @return int
     **/
    function getIteratorMode() {}

    /**
     * @return bool
     **/
    function isEmpty() {}

    /**
     * This function returns the current node index
     *
     * @return mixed
     **/
    function key() {}

    /**
     * Move the iterator to the next node.
     *
     * @return void
     **/
    function next() {}

    /**
     * @param mixed
     * @return bool
     **/
    function offsetExists($index) {}

    /**
     * @param mixed
     * @return mixed
     **/
    function offsetGet($index) {}

    /**
     * Sets the value at the specified index to newval.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function offsetSet($index, $newval) {}

    /**
     * Unsets the value at the specified index.
     *
     * @param mixed
     * @return void
     **/
    function offsetUnset($index) {}

    /**
     * @return mixed
     **/
    function pop() {}

    /**
     * Pushes value at the end of the doubly linked list.
     *
     * @param mixed
     * @return void
     **/
    function push($value) {}

    /**
     * This rewinds the iterator to the beginning.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * @param int
     * @return void
     **/
    function setIteratorMode($mode) {}

    /**
     * @return mixed
     **/
    function shift() {}

    /**
     * @return mixed
     **/
    function top() {}

    /**
     * Prepends value at the beginning of the doubly linked list.
     *
     * @param mixed
     * @return void
     **/
    function unshift($value) {}

    /**
     * Checks if the doubly linked list contains any more nodes.
     *
     * @return bool
     **/
    function valid() {}

}
class SplHeap implements Iterator, Countable {
    /**
     * Compare value1 with value2.
     *
     * @param mixed
     * @param mixed
     * @return int
     **/
    function compare($value1, $value2) {}

    /**
     * @return int
     **/
    function count() {}

    /**
     * Get the current datastructure node.
     *
     * @return mixed
     **/
    function current() {}

    /**
     * @return mixed
     **/
    function extract() {}

    /**
     * Insert value in the heap.
     *
     * @param mixed
     * @return void
     **/
    function insert($value) {}

    /**
     * @return bool
     **/
    function isEmpty() {}

    /**
     * This function returns the current node index
     *
     * @return mixed
     **/
    function key() {}

    /**
     * Extracts the top node from the heap.
     *
     * @return void
     **/
    function next() {}

    /**
     * @return void
     **/
    function recoverFromCorruption() {}

    /**
     * This rewinds the iterator to the beginning. This is a no-op for heaps
     * as the iterator is virtual and in fact never moves from the top of the 
     * heap.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * @return mixed
     **/
    function top() {}

    /**
     * Checks if the heap contains any more nodes.
     *
     * @return bool
     **/
    function valid() {}

}
class SplMaxHeap extends SplHeap implements Iterator, Countable {
    /**
     * Compare value1 with value2.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function compare($value1, $value2) {}

}
class SplMinHeap extends SplHeap implements Iterator, Countable {
    /**
     * Compare value1 with value2.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function compare($value1, $value2) {}

}
class SplPriorityQueue implements Iterator, Countable {
    /**
     * Compare priority1 with priority2.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function compare($priority1, $priority1) {}

    /**
     * @return int
     **/
    function count() {}

    /**
     * Get the current datastructure node.
     *
     * @return mixed
     **/
    function current() {}

    /**
     * @return mixed
     **/
    function extract() {}

    /**
     * Insert value with the priority priority in the queue.
     *
     * @param mixed
     * @param mixed
     * @return void
     **/
    function insert($value, $priority) {}

    /**
     * @return bool
     **/
    function isEmpty() {}

    /**
     * This function returns the current node index
     *
     * @return mixed
     **/
    function key() {}

    /**
     * Extracts the top node from the queue.
     *
     * @return void
     **/
    function next() {}

    /**
     * @return void
     **/
    function recoverFromCorruption() {}

    /**
     * This rewinds the iterator to the beginning. This is a no-op for heaps
     * as the iterator is virtual and in fact never moves from the top of the 
     * heap.
     *
     * @return void
     **/
    function rewind() {}

    /**
     * @param int
     * @return void
     **/
    function setExtractFlags($flags) {}

    /**
     * @return mixed
     **/
    function top() {}

    /**
     * Checks if the queue contains any more nodes.
     *
     * @return bool
     **/
    function valid() {}

}
class SplQueue extends SplDoublyLinkedList implements Iterator, ArrayAccess, Countable {
    /**
     * Dequeues value from the top of of the queue.
     *
     * @return mixed
     **/
    function dequeue() {}

    /**
     * Enqueues value at the end of the queue.
     *
     * @param mixed
     * @return void
     **/
    function enqueue($value) {}

    /**
     * @param int
     * @return void
     **/
    function setIteratorMode($mode) {}

}
class SplStack extends SplDoublyLinkedList implements Iterator, ArrayAccess, Countable {
    /**
     * @param int
     * @return void
     **/
    function setIteratorMode($mode) {}

}
class SplBool {
}
class SplEnum {
}
class SplFloat {
}
class SplInt {
}
class SQLite3 {
    /**
     * Returns the number of database rows that were changed (or inserted or
     * deleted) by the most recent SQL statement.
     *
     * @return int
     **/
    function changes() {}

    /**
     * Closes the database connection.
     *
     * @return bool
     **/
    function close() {}

    /**
     * Instantiates an SQLite3 object and opens a connection to an
     * SQLite 3 database. If the build includes encryption, then it will attempt
     * to use the key.
     *
     * @param string
     * @param int
     * @param string
     **/
    function __construct($filename, $flags, $encryption_key) {}

    /**
     * Registers a PHP function or user-defined function for use as an SQL
     * aggregate function for use within SQL statements.
     *
     * @param string
     * @param mixed
     * @param mixed
     * @param int
     * @return bool
     **/
    function createAggregate($name, $step_callback, $final_callback, $argument_count) {}

    /**
     * Registers a PHP function or user-defined function for use as an SQL scalar
     * function for use within SQL statements.
     *
     * @param string
     * @param mixed
     * @param int
     * @return bool
     **/
    function createFunction($name, $callback, $argument_count) {}

    /**
     * Returns a string that has been properly escaped for safe inclusion in an
     * SQL statement.
     *
     * @param string
     * @return string
     **/
    function escapeString($value) {}

    /**
     * Executes a result-less query against a given database.
     *
     * @param string
     * @return bool
     **/
    function exec($query) {}

    /**
     * Returns the numeric result code of the most recent failed SQLite request.
     *
     * @return int
     **/
    function lastErrorCode() {}

    /**
     * Returns English text describing the most recent failed SQLite request.
     *
     * @return string
     **/
    function lastErrorMsg() {}

    /**
     * Returns the row ID of the most recent INSERT into the database.
     *
     * @return int
     **/
    function lastInsertRowID() {}

    /**
     * Attempts to load an SQLite extension library.
     *
     * @param string
     * @return bool
     **/
    function loadExtension($shared_library) {}

    /**
     * Opens an SQLite 3 Database. If the build includes encryption, then it will
     * attempt to use the key.
     *
     * @param string
     * @param int
     * @param string
     * @return bool
     **/
    function open($filename, $flags, $encryption_key) {}

    /**
     * Prepares an SQL statement for execution and returns an SQLite3_stmt object.
     *
     * @param string
     * @return SQLite3_stmt
     **/
    function prepare($query) {}

    /**
     * Executes an SQL query, returning an SQLite3_result object if the query
     * returns results.
     *
     * @param string
     * @return SQLite3_result
     **/
    function query($query) {}

    /**
     * Executes a query and returns a single result.
     *
     * @param string
     * @param bool
     * @return SQLite3_result
     **/
    function querySingle($query, $entire_row) {}

    /**
     * Returns the SQLite3 library version as a string constant and as a number.
     *
     * @return array
     **/
    function version() {}

}
class SQLite3_result {
    /**
     * Returns the name of the column specified by the
     * column_number.
     *
     * @param int
     * @return string
     **/
    function columnName($column_number) {}

    /**
     * Returns the type of the column identified by
     * column_number.
     *
     * @param int
     * @return string
     **/
    function columnType($column_number) {}

    /**
     * Fetches a result row as an associative or numerically indexed array or both.
     * By default, fetches as both.
     *
     * @param int
     * @return array
     **/
    function fetchArray($mode) {}

    /**
     * Closes the result set.
     *
     * @return bool
     **/
    function finalize() {}

    /**
     * Returns the number of columns in the result set.
     *
     * @return int
     **/
    function numColumns() {}

    /**
     * Resets the result set back to the first row.
     *
     * @return bool
     **/
    function reset() {}

}
class SQLite3_stmt {
    /**
     * Binds a parameter to a statement variable.
     *
     * @param int
     * @param mixed
     * @param int
     * @return bool
     **/
    function bindParam($param_number, $param, $type) {}

    /**
     * Binds the value of a parameter to a statement variable.
     *
     * @param int
     * @param mixed
     * @param int
     * @return bool
     **/
    function bindValue($param_number, $param, $type) {}

    /**
     * Clears all current bound parameters.
     *
     * @return bool
     **/
    function clear() {}

    /**
     * Closes the prepared statement.
     *
     * @return bool
     **/
    function close() {}

    /**
     * Executes a prepared statement and returns a result set object.
     *
     * @return SQLite3_result
     **/
    function execute() {}

    /**
     * Returns the number of parameters within the prepared statement.
     *
     * @return int
     **/
    function paramCount() {}

    /**
     * Resets the prepared statement to its state prior to execution. All bindings
     * remain intact after reset.
     *
     * @return bool
     **/
    function reset() {}

}
class Swish {
    const META_TYPE_UNDEF = 0;
    const META_TYPE_STRING = 0;
    const META_TYPE_ULONG = 0;
    const META_TYPE_DATE = 0;
    const IN_FILE_BIT = 0;
    const IN_TITLE_BIT = 0;
    const IN_HEAD_BIT = 0;
    const IN_BODY_BIT = 0;
    const IN_COMMENTS_BIT = 0;
    const IN_HEADER_BIT = 0;
    const IN_EMPHASIZED_BIT = 0;
    const IN_META_BIT = 0;
    const IN_FILE = 0;
    const IN_TITLE = 0;
    const IN_HEAD = 0;
    const IN_BODY = 0;
    const IN_COMMENTS = 0;
    const IN_HEADER = 0;
    const IN_EMPHASIZED = 0;
    const IN_META = 0;
    const IN_ALL = 0;
    /**
     * @param string
     * @return void
     **/
    function __construct($index_names) {}

}
class tidy {
    /**
     * tidy::__construct constructs a new tidy object.
     *
     * @param string
     * @param mixed
     * @param string
     * @param bool
     * @return tidy
     **/
    function __construct($filename, $config, $encoding, $use_include_path) {}

}
class tidy_node {
    /**
     * @param int
     * @return tidy_attr
     **/
    function get_attr($attrib_id) {}

    /**
     * @param int
     * @return array
     **/
    function get_nodes($node_id) {}

    /**
     * @return tidy_node
     **/
    function next() {}

    /**
     * @return tidy_node
     **/
    function prev() {}

}
class tidyNode {
    /**
     * @return bool
     **/
    function hasChildren() {}

    /**
     * @return bool
     **/
    function hasSiblings() {}

    /**
     * This functions returns if the current node is ASP, or 
     * otherwise.
     *
     * @return bool
     **/
    function isAsp() {}

    /**
     * @return bool
     **/
    function isComment() {}

    /**
     * @return bool
     **/
    function isHtml() {}

    /**
     * @return bool
     **/
    function isJste() {}

    /**
     * Returns if the current node is PHP code, otherwise.
     *
     * @return bool
     **/
    function isPhp() {}

    /**
     * @return bool
     **/
    function isText() {}

    /**
     * Returns the parent node of the current node.
     *
     * @return tidyNode
     **/
    function getParent() {}

}
class XMLReader {
    /**
     * Closes the input the XMLReader object is currently parsing.
     *
     * @return bool
     **/
    function close() {}

    /**
     * This method copies the current node and returns the appropriate DOM object.
     *
     * @return DOMNode
     **/
    function expand() {}

    /**
     * Returns the value of a named attribute or an empty string if 
     * attribute does not exist or not positioned on an element node.
     *
     * @param string
     * @return string
     **/
    function getAttribute($name) {}

    /**
     * Returns the value of an attribute based on its position or an 
     * empty string if attribute does not exist or not positioned on 
     * an element node.
     *
     * @param int
     * @return string
     **/
    function getAttributeNo($index) {}

    /**
     * Returns the value of an attribute by name and namespace URI or an empty 
     * string if attribute does not exist or not positioned on an element node.
     *
     * @param string
     * @param string
     * @return string
     **/
    function getAttributeNs($localName, $namespaceURI) {}

    /**
     * Indicates if specified property has been set.
     *
     * @param int
     * @return bool
     **/
    function getParserProperty($property) {}

    /**
     * Returns a boolean indicating if the document being parsed is currently valid.
     *
     * @return bool
     **/
    function isValid() {}

    /**
     * Lookup in scope namespace for a given prefix.
     *
     * @param string
     * @return bool
     **/
    function lookupNamespace($prefix) {}

    /**
     * Positions cursor on the named attribute.
     *
     * @param string
     * @return bool
     **/
    function moveToAttribute($name) {}

    /**
     * Positions cursor on attribute based on its position.
     *
     * @param int
     * @return bool
     **/
    function moveToAttributeNo($index) {}

    /**
     * Positions cursor on the named attribute in specified namespace.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function moveToAttributeNs($localName, $namespaceURI) {}

    /**
     * Moves cursor to the parent Element of current Attribute.
     *
     * @return bool
     **/
    function moveToElement() {}

    /**
     * Moves cursor to the first Attribute.
     *
     * @return bool
     **/
    function moveToFirstAttribute() {}

    /**
     * Moves cursor to the next Attribute if positioned on an Attribute or 
     * moves to first attribute if positioned on an Element.
     *
     * @return bool
     **/
    function moveToNextAttribute() {}

    /**
     * Positions cursor on the next node skipping all subtrees.
     *
     * @param string
     * @return bool
     **/
    function next($localname) {}

    /**
     * Set the URI containing the XML document to be parsed.
     *
     * @param string
     * @param string
     * @param int
     * @return bool
     **/
    function open($URI, $encoding, $options) {}

    /**
     * Moves cursor to the next node in the document.
     *
     * @return bool
     **/
    function read() {}

    /**
     * Reads the contents of the current node, including child nodes and markup.
     *
     * @return string
     **/
    function readInnerXML() {}

    /**
     * Reads the contents of the current node, including the node itself.
     *
     * @return string
     **/
    function readOuterXML() {}

    /**
     * Reads the contents of the current node as an string.
     *
     * @return string
     **/
    function readString() {}

    /**
     * Set or Unset parser option for the parser. The options must be set 
     * after xmlreader-open or 
     * xmlreader-xml are called and before 
     * the first xmlreader-read call.
     *
     * @param int
     * @param bool
     * @return bool
     **/
    function setParserProperty($property, $value) {}

    /**
     * Set the filename or URI for the RelaxNG Schema to use for validation.
     *
     * @param string
     * @return bool
     **/
    function setRelaxNGSchema($filename) {}

    /**
     * Set the data containing a RelaxNG Schema to use for validation.
     *
     * @param string
     * @return bool
     **/
    function setRelaxNGSchemaSource($source) {}

    /**
     * Use W3C XSD schema to validate the document as it is processed. Activation
     * is only possible before the first Read().
     *
     * @param string
     * @return boolean
     **/
    function setSchema($filename) {}

    /**
     * Set the data containing the XML to parse.
     *
     * @param string
     * @param string
     * @param int
     * @return bool
     **/
    function xml($source, $encoding, $options) {}

}
class XSLTProcessor {
    /**
     * Gets a parameter if previously set by
     * XSLTProcessor::setParameter.
     *
     * @param string
     * @param string
     * @return string
     **/
    function getParameter($namespaceURI, $localName) {}

    /**
     * This method determine if PHP was built with the EXSLT library.
     *
     * @return bool
     **/
    function hasExsltSupport() {}

    /**
     * This method import the stylesheet into the 
     * XSLTProcessor for transformations.
     *
     * @param DOMDocument
     * @return void
     **/
    function importStylesheet($stylesheet) {}

    /**
     * This method enables the ability to use PHP functions as XSLT functions
     * within XSL stylesheets.
     *
     * @param mixed
     * @return void
     **/
    function registerPHPFunctions($restrict) {}

    /**
     * Removes a parameter, if set. This will make the processor use the
     * default value for the parameter as specified in the stylesheet.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function removeParameter($namespaceURI, $localName) {}

    /**
     * Sets the value of one or more parameters to be used in subsequent 
     * transformations with XSLTProcessor. If the 
     * parameter doesn't exist in the stylesheet it will be ignored.
     *
     * @param string
     * @param string
     * @param string
     * @return bool
     **/
    function setParameter($namespace, $name, $value) {}

    /**
     * Transforms the source node to a DOMDocument applying
     * the stylesheet given by the
     * XSLTProcessor::importStylesheet method.
     *
     * @param DOMNode
     * @return DOMDocument
     **/
    function transformToDoc($doc) {}

    /**
     * Transforms the source node to an URI applying the stylesheet given by the
     * XSLTProcessor::importStylesheet method.
     *
     * @param DOMDocument
     * @param string
     * @return int
     **/
    function transformToURI($doc, $uri) {}

    /**
     * Transforms the source node to a string applying the stylesheet given by
     * the xsltprocessor::importStylesheet method.
     *
     * @param DOMDocument
     * @return string
     **/
    function transformToXML($doc) {}

}
class ZipArchive {
    /**
     * Adds an empty directory in the archive.
     *
     * @param string
     * @return bool
     **/
    function addEmptyDir($dirname) {}

    /**
     * Adds a file to a ZIP archive from a given path
     *
     * @param string
     * @param string
     * @return bool
     **/
    function addFile($filename, $localname) {}

    /**
     * Add a file to a ZIP archive using its contents.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function addFromString($localname, $contents) {}

    /**
     * Close opened or created archive and save changes. This method is
     * automatically called at the end of the script.
     *
     * @return bool
     **/
    function close() {}

    /**
     * Delete an entry in the archive using its index.
     *
     * @param int
     * @return bool
     **/
    function deleteIndex($index) {}

    /**
     * Delete an entry in the archive using its name.
     *
     * @param string
     * @return bool
     **/
    function deleteName($name) {}

    /**
     * Extract the complete archive or the given files to the specified
     * destination.
     *
     * @param string
     * @param mixed
     * @return mixed
     **/
    function extractTo($destination, $entries) {}

    /**
     * Returns the Zip archive comment.
     *
     * @return string
     **/
    function getArchiveComment() {}

    /**
     * Returns the comment of an entry using the entry index.
     *
     * @param int
     * @param int
     * @return string
     **/
    function getCommentIndex($index, $flags) {}

    /**
     * Returns the comment of an entry using the entry name.
     *
     * @param string
     * @param int
     * @return string
     **/
    function getCommentName($name, $flags) {}

    /**
     * Returns the entry contents using its index.
     *
     * @param int
     * @param int
     * @return mixed
     **/
    function getFromIndex($index, $flags) {}

    /**
     * Returns the entry contents using its name.
     *
     * @param string
     * @param int
     * @return mixed
     **/
    function getFromName($name, $flags) {}

    /**
     * Returns the name of an entry using its index.
     *
     * @param int
     * @return string
     **/
    function getNameIndex($index) {}

    /**
     * Get a file handler to the entry defined by its name. For now it only
     * supports read operations.
     *
     * @param string
     * @return resource
     **/
    function getStream($name) {}

    /**
     * Locates an entry using its name.
     *
     * @param string
     * @param int
     * @return mixed
     **/
    function locateName($name, $flags) {}

    /**
     * Opens a new zip archive for reading, writing or modifying.
     *
     * @param string
     * @param int
     * @return mixed
     **/
    function open($filename, $flags) {}

    /**
     * Renames an entry defined by its index.
     *
     * @param int
     * @param string
     * @return bool
     **/
    function renameIndex($index, $newname) {}

    /**
     * Renames an entry defined by its name.
     *
     * @param string
     * @param string
     * @return bool
     **/
    function renameName($name, $newname) {}

    /**
     * Set the comment of a ZIP archive.
     *
     * @param string
     * @return mixed
     **/
    function setArchiveComment($comment) {}

    /**
     * Set the comment of an entry defined by its index.
     *
     * @param int
     * @param string
     * @return mixed
     **/
    function setCommentIndex($index, $comment) {}

    /**
     * Set the comment of an entry defined by its name.
     *
     * @param string
     * @param string
     * @return mixed
     **/
    function setCommentName($name, $comment) {}

    /**
     * The function obtains information about the entry defined by its
     * index.
     *
     * @param int
     * @param int
     * @return mixed
     **/
    function statIndex($index, $flags) {}

    /**
     * The function obtains information about the entry defined by its
     * name.
     *
     * @param name
     * @param int
     * @return mixed
     **/
    function statName($name, $flags) {}

    /**
     * Undo all changes done in the archive.
     *
     * @return mixed
     **/
    function unchangeAll() {}

    /**
     * Revert all global changes to the archive archive. For now, this
     * only reverts archive comment changes.
     *
     * @return mixed
     **/
    function unchangeArchive() {}

    /**
     * Revert all changes done to an entry at the given index.
     *
     * @param int
     * @return mixed
     **/
    function unchangeIndex($index) {}

    /**
     * Revert all changes done to an entry.
     *
     * @param string
     * @return mixed
     **/
    function unchangeName($name) {}

}
class stdClass {
}
class __PHP_Incomplete_Class {
}
class exception {
}
class php_user_filter {
}
class imagick {
    const COLOR_BLACK = 0;
    const COLOR_BLUE = 0;
    const COLOR_CYAN = 0;
    const COLOR_GREEN = 0;
    const COLOR_RED = 0;
    const COLOR_YELLOW = 0;
    const COLOR_MAGENTA = 0;
    const COLOR_OPACITY = 0;
    const COLOR_ALPHA = 0;
    const COLOR_FUZZ = 0;
}
class ZIPARCHIVE {
    const CREATE = 0;
    const OVERWRITE = 0;
    const EXCL = 0;
    const CHECKCONS = 0;
    const FL_NOCASE = 0;
    const FL_NODIR = 0;
    const FL_COMPRESSED = 0;
    const FL_UNCHANGED = 0;
    const CM_DEFAULT = 0;
    const CM_STORE = 0;
    const CM_SHRINK = 0;
    const CM_REDUCE_1 = 0;
    const CM_REDUCE_2 = 0;
    const CM_REDUCE_3 = 0;
    const CM_REDUCE_4 = 0;
    const CM_IMPLODE = 0;
    const CM_DEFLATE = 0;
    const CM_DEFLATE64 = 0;
    const CM_PKWARE_IMPLODE = 0;
    const CM_BZIP2 = 0;
    const ER_OK = 0;
    const ER_MULTIDISK = 0;
    const ER_RENAME = 0;
    const ER_CLOSE = 0;
    const ER_SEEK = 0;
    const ER_READ = 0;
    const ER_WRITE = 0;
    const ER_CRC = 0;
    const ER_ZIPCLOSED = 0;
    const ER_NOENT = 0;
    const ER_EXISTS = 0;
    const ER_OPEN = 0;
    const ER_TMPOPEN = 0;
    const ER_ZLIB = 0;
    const ER_MEMORY = 0;
    const ER_CHANGED = '';
    const ER_COMPNOTSUPP = 0;
    const ER_EOF = 0;
    const ER_INVAL = 0;
    const ER_NOZIP = 0;
    const ER_INTERNAL = 0;
    const ER_INCONS = 0;
    const ER_REMOVE = 0;
    const ER_DELETED = 0;
}
define('COUNT_NORMAL', 0);
define('COUNT_RECURSIVE', 0);
define('EXTR_OVERWRITE', 0);
define('EXTR_SKIP', 0);
define('EXTR_PREFIX_SAME', 0);
define('EXTR_PREFIX_ALL', 0);
define('EXTR_PREFIX_INVALID', 0);
define('EXTR_PREFIX_IF_EXISTS', 0);
define('EXTR_IF_EXISTS', 0);
define('EXTR_REFS', 0);
define('BBCODE_TYPE_NOARG', 0);
define('BBCODE_TYPE_SINGLE', 0);
define('BBCODE_TYPE_ARG', 0);
define('BBCODE_TYPE_OPTARG', 0);
define('BBCODE_TYPE_ROOT', 0);
define('BBCODE_FLAGS_ARG_PARSING', 0);
define('BBCODE_FLAGS_CDATA_NOT_ALLOWED', 0);
define('BBCODE_FLAGS_SMILEYS_ON', 0);
define('BBCODE_FLAGS_SMILEYS_OFF', 0);
define('BBCODE_FLAGS_ONE_OPEN_PER_LEVEL', 0);
define('BBCODE_FLAGS_REMOVE_IF_EMPTY', 0);
define('BBCODE_FLAGS_DENY_REOPEN_CHILD', 0);
define('BBCODE_ARG_DOUBLE_QUOTE', 0);
define('BBCODE_ARG_SINGLE_QUOTE', 0);
define('BBCODE_ARG_HTML_QUOTE', 0);
define('BBCODE_ARG_QUOTE_ESCAPING', 0);
define('BBCODE_AUTO_CORRECT', 0);
define('BBCODE_CORRECT_REOPEN_TAGS', 0);
define('BBCODE_DISABLE_TREE_BUILD', 0);
define('BBCODE_DEFAULT_SMILEYS_ON', 0);
define('BBCODE_DEFAULT_SMILEYS_OFF', 0);
define('BBCODE_FORCE_SMILEYS_OFF', 0);
define('BBCODE_SMILEYS_CASE_INSENSITIVE', 0);
define('BBCODE_SET_FLAGS_SET', 0);
define('BBCODE_SET_FLAGS_ADD', 0);
define('BBCODE_SET_FLAGS_REMOVE', 0);
define('CAL_GREGORIAN', 0);
define('CAL_JULIAN', 0);
define('CAL_JEWISH', 0);
define('CAL_FRENCH', 0);
define('CAL_NUM_CALS', 0);
define('CAL_DOW_DAYNO', 0);
define('CAL_DOW_SHORT', 0);
define('CAL_DOW_LONG', 0);
define('CAL_MONTH_GREGORIAN_SHORT', 0);
define('CAL_MONTH_GREGORIAN_LONG', 0);
define('CAL_MONTH_JULIAN_SHORT', 0);
define('CAL_MONTH_JULIAN_LONG', 0);
define('CAL_MONTH_JEWISH', 0);
define('CAL_MONTH_FRENCH', 0);
define('CLSCTX_INPROC_SERVER', 0);
define('CLSCTX_INPROC_HANDLER', 0);
define('CLSCTX_LOCAL_SERVER', 0);
define('CLSCTX_REMOTE_SERVER', 0);
define('CLSCTX_SERVER', 0);
define('CLSCTX_ALL', 0);
define('VT_NULL', 0);
define('VT_EMPTY', 0);
define('VT_UI1', 0);
define('VT_I2', 0);
define('VT_I4', 0);
define('VT_R4', 0);
define('VT_R8', 0);
define('VT_BOOL', 0);
define('VT_ERROR', 0);
define('VT_CY', 0);
define('VT_DATE', 0);
define('VT_BSTR', 0);
define('VT_DECIMAL', 0);
define('VT_UNKNOWN', 0);
define('VT_DISPATCH', 0);
define('VT_VARIANT', 0);
define('VT_I1', 0);
define('VT_UI2', 0);
define('VT_UI4', 0);
define('VT_INT', 0);
define('VT_UINT', 0);
define('VT_ARRAY', 0);
define('VT_BYREF', 0);
define('CP_ACP', 0);
define('CP_MACCP', 0);
define('CP_OEMCP', 0);
define('CP_UTF7', 0);
define('CP_UTF8', 0);
define('CP_SYMBOL', 0);
define('CP_THREAD_ACP', 0);
define('VARCMP_LT', 0);
define('VARCMP_EQ', 0);
define('VARCMP_GT', 0);
define('VARCMP_NULL', 0);
define('NORM_IGNORECASE', 0);
define('NORM_IGNORENONSPACE', 0);
define('NORM_IGNORESYMBOLS', 0);
define('NORM_IGNOREWIDTH', 0);
define('NORM_IGNOREKANATYPE', 0);
define('NORM_IGNOREKASHIDA', 0);
define('DISP_E_DIVBYZERO', 0);
define('DISP_E_OVERFLOW', 0);
define('MK_E_UNAVAILABLE', 0);
define('CURLOPT_AUTOREFERER', 0);
define('CURLOPT_COOKIESESSION', 0);
define('CURLOPT_DNS_USE_GLOBAL_CACHE', 0);
define('CYRUS_CONN_NONSYNCLITERAL', 0);
define('CYRUS_CONN_INITIALRESPONSE', 0);
define('CYRUS_CALLBACK_NUMBERED', 0);
define('CYRUS_CALLBACK_NOLITERAL', 0);
define('DATE_ATOM', '');
define('DATE_COOKIE', '');
define('DATE_ISO8601', '');
define('DATE_RFC822', '');
define('DATE_RFC850', '');
define('DATE_RFC1036', '');
define('DATE_RFC1123', '');
define('DATE_RFC2822', '');
define('DATE_RFC3339', '');
define('DATE_RSS', '');
define('DATE_W3C', '');
define('DBX_MYSQL', 0);
define('DBX_ODBC', 0);
define('DBX_PGSQL', 0);
define('DBX_MSSQL', 0);
define('DBX_FBSQL', 0);
define('DBX_OCI8', 0);
define('DBX_SYBASECT', 0);
define('DBX_SQLITE', 0);
define('DBX_PERSISTENT', 0);
define('DBX_RESULT_INFO', 0);
define('DBX_RESULT_INDEX', 0);
define('DBX_RESULT_ASSOC', 0);
define('DBX_RESULT_UNBUFFERED', 0);
define('DBX_COLNAMES_UNCHANGED', 0);
define('DBX_COLNAMES_UPPERCASE', 0);
define('DBX_COLNAMES_LOWERCASE', 0);
define('DBX_CMP_NATIVE', 0);
define('DBX_CMP_TEXT', 0);
define('DBX_CMP_NUMBER', 0);
define('DBX_CMP_ASC', 0);
define('DBX_CMP_DESC', 0);
define('F_DUPFD', 0);
define('F_GETFD', 0);
define('F_GETFL', 0);
define('F_GETLK', 0);
define('F_GETOWN', 0);
define('F_RDLCK', 0);
define('F_SETFL', 0);
define('F_SETLK', 0);
define('F_SETLKW', 0);
define('F_SETOWN', 0);
define('F_UNLCK', 0);
define('F_WRLCK', 0);
define('O_APPEND', 0);
define('O_ASYNC', 0);
define('O_CREAT', 0);
define('O_EXCL', 0);
define('O_NDELAY', 0);
define('O_NOCTTY', 0);
define('O_NONBLOCK', 0);
define('O_RDONLY', 0);
define('O_RDWR', 0);
define('O_SYNC', 0);
define('O_TRUNC', 0);
define('O_WRONLY', 0);
define('S_IRGRP', 0);
define('S_IROTH', 0);
define('S_IRUSR', 0);
define('S_IRWXG', 0);
define('S_IRWXO', 0);
define('S_IRWXU', 0);
define('S_IWGRP', 0);
define('S_IWOTH', 0);
define('S_IWUSR', 0);
define('S_IXGRP', 0);
define('S_IXOTH', 0);
define('S_IXUSR', 0);
define('DIRECTORY_SEPARATOR', '');
define('PATH_SEPARATOR', '');
define('EXP_GLOB', 0);
define('EXP_EXACT', 0);
define('EXP_REGEXP', 0);
define('EXP_EOF', 0);
define('EXP_TIMEOUT', 0);
define('EXP_FULLBUFFER', 0);
define('FBSQL_ASSOC', 0);
define('FBSQL_NUM', 0);
define('FBSQL_BOTH', 0);
define('FBSQL_LOCK_DEFERRED', 0);
define('FBSQL_LOCK_OPTIMISTIC', 0);
define('FBSQL_LOCK_PESSIMISTIC', 0);
define('FBSQL_ISO_READ_UNCOMMITTED', 0);
define('FBSQL_ISO_READ_COMMITTED', 0);
define('FBSQL_ISO_REPEATABLE_READ', 0);
define('FBSQL_ISO_SERIALIZABLE', 0);
define('FBSQL_ISO_VERSIONED', 0);
define('FBSQL_UNKNOWN', 0);
define('FBSQL_STOPPED', 0);
define('FBSQL_STARTING', 0);
define('FBSQL_RUNNING', 0);
define('FBSQL_STOPPING', 0);
define('FBSQL_NOEXEC', 0);
define('FBSQL_LOB_DIRECT', 0);
define('FBSQL_LOB_HANDLE', 0);
define('FDFValue', 0);
define('FDFStatus', 0);
define('FDFFile', 0);
define('FDFID', 0);
define('FDFFf', 0);
define('FDFSetFf', 0);
define('FDFClearFf', 0);
define('FDFFlags', 0);
define('FDFSetF', 0);
define('FDFClrF', 0);
define('FDFAP', 0);
define('FDFAS', 0);
define('FDFAction', 0);
define('FDFAA', 0);
define('FDFAPRef', 0);
define('FDFIF', 0);
define('FDFEnter', 0);
define('FDFExit', 0);
define('FDFDown', 0);
define('FDFUp', 0);
define('FDFFormat', 0);
define('FDFValidate', 0);
define('FDFKeystroke', 0);
define('FDFCalculate', 0);
define('FDFNormalAP', 0);
define('FDFRolloverAP', 0);
define('FDFDownAP', 0);
define('FILEINFO_NONE', 0);
define('FILEINFO_SYMLINK', 0);
define('FILEINFO_MIME', 0);
define('FILEINFO_COMPRESS', 0);
define('FILEINFO_DEVICES', 0);
define('FILEINFO_CONTINUE', 0);
define('FILEINFO_PRESERVE_ATIME', 0);
define('FILEINFO_RAW', 0);
define('GLOB_BRACE', 0);
define('GLOB_ONLYDIR', 0);
define('GLOB_MARK', 0);
define('GLOB_NOSORT', 0);
define('GLOB_NOCHECK', 0);
define('GLOB_NOESCAPE', 0);
define('PATHINFO_DIRNAME', 0);
define('PATHINFO_BASENAME', 0);
define('PATHINFO_EXTENSION', 0);
define('PATHINFO_FILENAME', 0);
define('FILE_USE_INCLUDE_PATH', 0);
define('FILE_APPEND', 0);
define('FILE_IGNORE_NEW_LINES', 0);
define('FILE_SKIP_EMPTY_LINES', 0);
define('FILE_BINARY', 0);
define('FILE_TEXT', 0);
define('INPUT_POST', 0);
define('INPUT_GET', 0);
define('INPUT_COOKIE', 0);
define('INPUT_ENV', 0);
define('INPUT_SERVER', 0);
define('INPUT_SESSION', 0);
define('INPUT_REQUEST', 0);
define('FILTER_FLAG_NONE', 0);
define('FILTER_REQUIRE_SCALAR', 0);
define('FILTER_REQUIRE_ARRAY', 0);
define('FILTER_FORCE_ARRAY', 0);
define('FILTER_NULL_ON_FAILURE', 0);
define('FILTER_VALIDATE_INT', 0);
define('FILTER_VALIDATE_BOOLEAN', 0);
define('FILTER_VALIDATE_FLOAT', 0);
define('FILTER_VALIDATE_REGEXP', 0);
define('FILTER_VALIDATE_URL', 0);
define('FILTER_VALIDATE_EMAIL', 0);
define('FILTER_VALIDATE_IP', 0);
define('FILTER_DEFAULT', 0);
define('FILTER_UNSAFE_RAW', 0);
define('FILTER_SANITIZE_STRING', 0);
define('FILTER_SANITIZE_STRIPPED', 0);
define('FILTER_SANITIZE_ENCODED', 0);
define('FILTER_SANITIZE_SPECIAL_CHARS', 0);
define('FILTER_SANITIZE_EMAIL', 0);
define('FILTER_SANITIZE_URL', 0);
define('FILTER_SANITIZE_NUMBER_INT', 0);
define('FILTER_SANITIZE_NUMBER_FLOAT', 0);
define('FILTER_SANITIZE_MAGIC_QUOTES', 0);
define('FILTER_CALLBACK', 0);
define('FILTER_FLAG_ALLOW_OCTAL', 0);
define('FILTER_FLAG_ALLOW_HEX', 0);
define('FILTER_FLAG_STRIP_LOW', 0);
define('FILTER_FLAG_STRIP_HIGH', 0);
define('FILTER_FLAG_ENCODE_LOW', 0);
define('FILTER_FLAG_ENCODE_HIGH', 0);
define('FILTER_FLAG_ENCODE_AMP', 0);
define('FILTER_FLAG_NO_ENCODE_QUOTES', 0);
define('FILTER_FLAG_EMPTY_STRING_NULL', 0);
define('FILTER_FLAG_ALLOW_FRACTION', 0);
define('FILTER_FLAG_ALLOW_THOUSAND', 0);
define('FILTER_FLAG_ALLOW_SCIENTIFIC', 0);
define('FILTER_FLAG_SCHEME_REQUIRED', 0);
define('FILTER_FLAG_HOST_REQUIRED', 0);
define('FILTER_FLAG_PATH_REQUIRED', 0);
define('FILTER_FLAG_QUERY_REQUIRED', 0);
define('FILTER_FLAG_IPV4', 0);
define('FILTER_FLAG_IPV6', 0);
define('FILTER_FLAG_NO_RES_RANGE', 0);
define('FILTER_FLAG_NO_PRIV_RANGE', 0);
define('FRIBIDI_CHARSET_UTF8', 0);
define('FRIBIDI_CHARSET_8859_6', 0);
define('FRIBIDI_CHARSET_8859_8', 0);
define('FRIBIDI_CHARSET_CP1255', 0);
define('FRIBIDI_CHARSET_CP1256', 0);
define('FRIBIDI_CHARSET_ISIRI_3342', 0);
define('FRIBIDI_CHARSET_CAP_RTL', 0);
define('FRIBIDI_RTL', 0);
define('FRIBIDI_LTR', 0);
define('FRIBIDI_AUTO', 0);
define('FTP_ASCII', 0);
define('FTP_TEXT', 0);
define('FTP_BINARY', 0);
define('FTP_IMAGE', 0);
define('FTP_TIMEOUT_SEC', 0);
define('GEOIP_COUNTRY_EDITION', 0);
define('GEOIP_REGION_EDITION_REV0', 0);
define('GEOIP_CITY_EDITION_REV0', 0);
define('GEOIP_ORG_EDITION', 0);
define('GEOIP_ISP_EDITION', 0);
define('GEOIP_CITY_EDITION_REV1', 0);
define('GEOIP_REGION_EDITION_REV1', 0);
define('GEOIP_PROXY_EDITION', 0);
define('GEOIP_ASNUM_EDITION', 0);
define('GEOIP_NETSPEED_EDITION', 0);
define('GEOIP_DOMAIN_EDITION', 0);
define('GMP_ROUND_ZERO', 0);
define('GMP_ROUND_PLUSINF', 0);
define('GMP_ROUND_MINUSINF', 0);
define('GMP_VERSION', '');
define('GNUPG_SIG_MODE_NORMAL', 0);
define('GNUPG_SIG_MODE_DETACH', 0);
define('GNUPG_SIG_MODE_CLEAR', 0);
define('GNUPG_VALIDITY_UNKNOWN', 0);
define('GNUPG_VALIDITY_UNDEFINED', 0);
define('GNUPG_VALIDITY_NEVER', 0);
define('GNUPG_VALIDITY_MARGINAL', 0);
define('GNUPG_VALIDITY_FULL', 0);
define('GNUPG_VALIDITY_ULTIMATE', 0);
define('GNUPG_PROTOCOL_OpenPGP', 0);
define('GNUPG_PROTOCOL_CMS', 0);
define('GNUPG_SIGSUM_VALID', 0);
define('GNUPG_SIGSUM_GREEN', 0);
define('GNUPG_SIGSUM_RED', 0);
define('GNUPG_SIGSUM_KEY_REVOKED', 0);
define('GNUPG_SIGSUM_KEY_EXPIRED', 0);
define('GNUPG_SIGSUM_KEY_MISSING', 0);
define('GNUPG_SIGSUM_SIG_EXPIRED', 0);
define('GNUPG_SIGSUM_CRL_MISSING', 0);
define('GNUPG_SIGSUM_CRL_TOO_OLD', 0);
define('GNUPG_SIGSUM_BAD_POLICY', 0);
define('GNUPG_SIGSUM_SYS_ERROR', 0);
define('GNUPG_ERROR_WARNING', 0);
define('GNUPG_ERROR_EXCEPTION', 0);
define('GNUPG_ERROR_SILENT', 0);
define('HASH_HMAC', 0);
define('HTTP_SUPPORT', 0);
define('HTTP_SUPPORT_REQUESTS', 0);
define('HTTP_SUPPORT_MAGICMIME', 0);
define('HTTP_SUPPORT_ENCODINGS', 0);
define('HTTP_SUPPORT_SSLREQUESTS', 0);
define('HW_ATTR_LANG', 0);
define('HW_ATTR_NR', 0);
define('HW_ATTR_NONE', 0);
define('DB2_BINARY', 0);
define('DB2_CONVERT', 0);
define('DB2_PASSTHRU', 0);
define('DB2_SCROLLABLE', 0);
define('DB2_FORWARD_ONLY', 0);
define('DB2_PARAM_IN', 0);
define('DB2_PARAM_OUT', 0);
define('DB2_PARAM_INOUT', 0);
define('DB2_PARAM_FILE', 0);
define('DB2_AUTOCOMMIT_ON', 0);
define('DB2_AUTOCOMMIT_OFF', 0);
define('DB2_DOUBLE', 0);
define('DB2_LONG', 0);
define('DB2_CHAR', 0);
define('DB2_CASE_NATURAL', 0);
define('DB2_CASE_LOWER', 0);
define('DB2_CASE_UPPER', 0);
define('DB2_DEFERRED_PREPARE_ON', 0);
define('DB2_DEFERRED_PREPARE_OFF', 0);
define('IFX_SCROLL', 0);
define('IFX_HOLD', 0);
define('IFX_LO_RDONLY', 0);
define('IFX_LO_WRONLY', 0);
define('IFX_LO_APPEND', 0);
define('IFX_LO_RDWR', 0);
define('IFX_LO_BUFFER', 0);
define('IFX_LO_NOBUFFER', 0);
define('IIS_READ', 0);
define('IIS_WRITE', 0);
define('IIS_EXECUTE', 0);
define('IIS_SCRIPT', 0);
define('IIS_ANONYMOUS', 0);
define('IIS_BASIC', 0);
define('IIS_NTLM', 0);
define('IIS_STARTING', 0);
define('IIS_STOPPED', 0);
define('IIS_PAUSED', 0);
define('IIS_RUNNING', 0);
define('GD_VERSION', '');
define('GD_MAJOR_VERSION', 0);
define('GD_MINOR_VERSION', 0);
define('GD_RELEASE_VERSION', 0);
define('GD_EXTRA_VERSION', '');
define('GD_BUNDLE', 0);
define('IMG_GIF', 0);
define('IMG_JPG', 0);
define('IMG_JPEG', 0);
define('IMG_PNG', 0);
define('IMG_WBMP', 0);
define('IMG_XPM', 0);
define('IMG_COLOR_TILED', 0);
define('IMG_COLOR_STYLED', 0);
define('IMG_COLOR_BRUSHED', 0);
define('IMG_COLOR_STYLEDBRUSHED', 0);
define('IMG_COLOR_TRANSPARENT', 0);
define('IMG_ARC_ROUNDED', 0);
define('IMG_ARC_PIE', 0);
define('IMG_ARC_CHORD', 0);
define('IMG_ARC_NOFILL', 0);
define('IMG_ARC_EDGED', 0);
define('IMG_GD2_RAW', 0);
define('IMG_GD2_COMPRESSED', 0);
define('IMG_EFFECT_REPLACE', 0);
define('IMG_EFFECT_ALPHABLEND', 0);
define('IMG_EFFECT_NORMAL', 0);
define('IMG_EFFECT_OVERLAY', 0);
define('IMG_FILTER_NEGATE', 0);
define('IMG_FILTER_GRAYSCALE', 0);
define('IMG_FILTER_BRIGHTNESS', 0);
define('IMG_FILTER_CONTRAST', 0);
define('IMG_FILTER_COLORIZE', 0);
define('IMG_FILTER_EDGEDETECT', 0);
define('IMG_FILTER_GAUSSIAN_BLUR', 0);
define('IMG_FILTER_SELECTIVE_BLUR', 0);
define('IMG_FILTER_EMBOSS', 0);
define('IMG_FILTER_MEAN_REMOVAL', 0);
define('IMG_FILTER_SMOOTH', 0);
define('IMAGETYPE_GIF', 0);
define('IMAGETYPE_JPEG', 0);
define('IMAGETYPE_PNG', 0);
define('IMAGETYPE_SWF', 0);
define('IMAGETYPE_PSD', 0);
define('IMAGETYPE_BMP', 0);
define('IMAGETYPE_WBMP', 0);
define('IMAGETYPE_XBM', 0);
define('IMAGETYPE_TIFF_II', 0);
define('IMAGETYPE_TIFF_MM', 0);
define('IMAGETYPE_IFF', 0);
define('IMAGETYPE_JB2', 0);
define('IMAGETYPE_JPC', 0);
define('IMAGETYPE_JP2', 0);
define('IMAGETYPE_JPX', 0);
define('IMAGETYPE_SWC', 0);
define('IMAGETYPE_ICO', 0);
define('PNG_NO_FILTER', 0);
define('PNG_FILTER_NONE', 0);
define('PNG_FILTER_SUB', 0);
define('PNG_FILTER_UP', 0);
define('PNG_FILTER_AVG', 0);
define('PNG_FILTER_PAETH', 0);
define('PNG_ALL_FILTERS', 0);
define('NIL', 0);
define('OP_DEBUG', 0);
define('OP_READONLY', 0);
define('OP_ANONYMOUS', 0);
define('OP_SHORTCACHE', 0);
define('OP_SILENT', 0);
define('OP_PROTOTYPE', 0);
define('OP_HALFOPEN', 0);
define('OP_EXPUNGE', 0);
define('OP_SECURE', 0);
define('CL_EXPUNGE', 0);
define('FT_UID', 0);
define('FT_PEEK', 0);
define('FT_NOT', 0);
define('FT_INTERNAL', 0);
define('FT_PREFETCHTEXT', 0);
define('ST_UID', 0);
define('ST_SILENT', 0);
define('ST_SET', 0);
define('CP_UID', 0);
define('CP_MOVE', 0);
define('SE_UID', 0);
define('SE_FREE', 0);
define('SE_NOPREFETCH', 0);
define('SO_FREE', 0);
define('SO_NOSERVER', 0);
define('SA_MESSAGES', 0);
define('SA_RECENT', 0);
define('SA_UNSEEN', 0);
define('SA_UIDNEXT', 0);
define('SA_UIDVALIDITY', 0);
define('SA_ALL', 0);
define('LATT_NOINFERIORS', 0);
define('LATT_NOSELECT', 0);
define('LATT_MARKED', 0);
define('LATT_UNMARKED', 0);
define('SORTDATE', 0);
define('SORTARRIVAL', 0);
define('SORTFROM', 0);
define('SORTSUBJECT', 0);
define('SORTTO', 0);
define('SORTCC', 0);
define('SORTSIZE', 0);
define('TYPETEXT', 0);
define('TYPEMULTIPART', 0);
define('TYPEMESSAGE', 0);
define('TYPEAPPLICATION', 0);
define('TYPEAUDIO', 0);
define('TYPEIMAGE', 0);
define('TYPEVIDEO', 0);
define('TYPEOTHER', 0);
define('ENC7BIT', 0);
define('ENC8BIT', 0);
define('ENCBINARY', 0);
define('ENCBASE64', 0);
define('ENCQUOTEDPRINTABLE', 0);
define('ENCOTHER', 0);
define('IMAP_OPENTIMEOUT', 0);
define('IMAP_READTIMEOUT', 0);
define('IMAP_WRITETIMEOUT', 0);
define('IMAP_CLOSETIMEOUT', 0);
define('LATT_REFERRAL', 0);
define('LATT_HASCHILDREN', 0);
define('LATT_HASNOCHILDREN', 0);
define('TYPEMODEL', 0);
define('ASSERT_ACTIVE', 0);
define('ASSERT_CALLBACK', 0);
define('ASSERT_BAIL', 0);
define('ASSERT_WARNING', 0);
define('ASSERT_QUIET_EVAL', 0);
define('INGRES_ASSOC', 0);
define('INGRES_NUM', 0);
define('INGRES_BOTH', 0);
define('INGRES_EXT_VERSION', '');
define('INGRES_API_VERSION', 0);
define('INGRES_CURSOR_READONLY', 0);
define('INGRES_CURSOR_UPDATE', 0);
define('INGRES_DATE_MULTINATIONAL', 0);
define('INGRES_DATE_MULTINATIONAL4', 0);
define('INGRES_DATE_FINNISH', 0);
define('INGRES_DATE_ISO', 0);
define('INGRES_DATE_ISO4', 0);
define('INGRES_DATE_GERMAN', 0);
define('INGRES_DATE_MDY', 0);
define('INGRES_DATE_DMY', 0);
define('INGRES_DATE_YMD', 0);
define('INGRES_MONEY_LEADING', 0);
define('INGRES_MONEY_TRAILING', 0);
define('INGRES_STRUCTURE_BTREE', 0);
define('INGRES_STRUCTURE_CBTREE', 0);
define('INGRES_STRUCTURE_HASH', 0);
define('INGRES_STRUCTURE_CHASH', 0);
define('INGRES_STRUCTURE_HEAP', 0);
define('INGRES_STRUCTURE_CHEAP', 0);
define('INGRES_STRUCTURE_ISAM', 0);
define('INGRES_STRUCTURE_CISAM', 0);
define('LDAP_DEREF_NEVER', 0);
define('LDAP_DEREF_SEARCHING', 0);
define('LDAP_DEREF_FINDING', 0);
define('LDAP_DEREF_ALWAYS', 0);
define('LDAP_OPT_DEREF', 0);
define('LDAP_OPT_SIZELIMIT', 0);
define('LDAP_OPT_TIMELIMIT', 0);
define('LDAP_OPT_NETWORK_TIMEOUT', 0);
define('LDAP_OPT_PROTOCOL_VERSION', 0);
define('LDAP_OPT_ERROR_NUMBER', 0);
define('LDAP_OPT_REFERRALS', 0);
define('LDAP_OPT_RESTART', 0);
define('LDAP_OPT_HOST_NAME', 0);
define('LDAP_OPT_ERROR_STRING', 0);
define('LDAP_OPT_MATCHED_DN', 0);
define('LDAP_OPT_SERVER_CONTROLS', 0);
define('LDAP_OPT_CLIENT_CONTROLS', 0);
define('LDAP_OPT_DEBUG_LEVEL', 0);
define('GSLC_SSL_NO_AUTH', 0);
define('GSLC_SSL_ONEWAY_AUTH', 0);
define('GSLC_SSL_TWOWAY_AUTH', 0);
define('LIBXML_COMPACT', 0);
define('LIBXML_DTDATTR', 0);
define('LIBXML_DTDLOAD', 0);
define('LIBXML_DTDVALID', 0);
define('LIBXML_NOBLANKS', 0);
define('LIBXML_NOCDATA', 0);
define('LIBXML_NOEMPTYTAG', 0);
define('LIBXML_NOENT', 0);
define('LIBXML_NOERROR', 0);
define('LIBXML_NONET', 0);
define('LIBXML_NOWARNING', 0);
define('LIBXML_NOXMLDECL', 0);
define('LIBXML_NSCLEAN', 0);
define('LIBXML_XINCLUDE', 0);
define('LIBXML_ERR_ERROR', 0);
define('LIBXML_ERR_FATAL', 0);
define('LIBXML_ERR_NONE', 0);
define('LIBXML_ERR_WARNING', 0);
define('LIBXML_VERSION', 0);
define('LIBXML_DOTTED_VERSION', '');
define('MAILPARSE_EXTRACT_OUTPUT', 0);
define('MAILPARSE_EXTRACT_STREAM', 0);
define('MAILPARSE_EXTRACT_RETURN', 0);
define('MB_OVERLOAD_MAIL', 0);
define('MB_OVERLOAD_STRING', 0);
define('MB_OVERLOAD_REGEX', 0);
define('MB_CASE_UPPER', 0);
define('MB_CASE_LOWER', 0);
define('MB_CASE_TITLE', 0);
define('M_PENDING', 0);
define('M_DONE', 0);
define('M_ERROR', 0);
define('M_FAIL', 0);
define('M_SUCCESS', 0);
define('MING_NEW', 0);
define('MING_ZLIB', 0);
define('SWFBUTTON_HIT', 0);
define('SWFBUTTON_DOWN', 0);
define('SWFBUTTON_OVER', 0);
define('SWFBUTTON_UP', 0);
define('SWFBUTTON_MOUSEUPOUTSIDE', 0);
define('SWFBUTTON_DRAGOVER', 0);
define('SWFBUTTON_DRAGOUT', 0);
define('SWFBUTTON_MOUSEUP', 0);
define('SWFBUTTON_MOUSEDOWN', 0);
define('SWFBUTTON_MOUSEOUT', 0);
define('SWFBUTTON_MOUSEOVER', 0);
define('SWFFILL_RADIAL_GRADIENT', 0);
define('SWFFILL_LINEAR_GRADIENT', 0);
define('SWFFILL_TILED_BITMAP', 0);
define('SWFFILL_CLIPPED_BITMAP', 0);
define('SWFTEXTFIELD_HASLENGTH', 0);
define('SWFTEXTFIELD_NOEDIT', 0);
define('SWFTEXTFIELD_PASSWORD', 0);
define('SWFTEXTFIELD_MULTILINE', 0);
define('SWFTEXTFIELD_WORDWRAP', 0);
define('SWFTEXTFIELD_DRAWBOX', 0);
define('SWFTEXTFIELD_NOSELECT', 0);
define('SWFTEXTFIELD_HTML', 0);
define('SWFTEXTFIELD_ALIGN_LEFT', 0);
define('SWFTEXTFIELD_ALIGN_RIGHT', 0);
define('SWFTEXTFIELD_ALIGN_CENTER', 0);
define('SWFTEXTFIELD_ALIGN_JUSTIFY', 0);
define('SWFACTION_ONLOAD', 0);
define('SWFACTION_ENTERFRAME', 0);
define('SWFACTION_UNLOAD', 0);
define('SWFACTION_MOUSEMOVE', 0);
define('SWFACTION_MOUSEDOWN', 0);
define('SWFACTION_MOUSEUP', 0);
define('SWFACTION_KEYDOWN', 0);
define('SWFACTION_KEYUP', 0);
define('SWFACTION_DATA', 0);
define('CONNECTION_ABORTED', 0);
define('CONNECTION_NORMAL', 0);
define('CONNECTION_TIMEOUT', 0);
define('__COMPILER_HALT_OFFSET__', 0);
define('UDM_FIELD_URLID', 0);
define('UDM_FIELD_URL', 0);
define('UDM_FIELD_CONTENT', 0);
define('UDM_FIELD_TITLE', 0);
define('UDM_FIELD_KEYWORDS', 0);
define('UDM_FIELD_DESC', 0);
define('UDM_FIELD_DESCRIPTION', 0);
define('UDM_FIELD_TEXT', 0);
define('UDM_FIELD_SIZE', 0);
define('UDM_FIELD_RATING', 0);
define('UDM_FIELD_SCORE', 0);
define('UDM_FIELD_MODIFIED', 0);
define('UDM_FIELD_ORDER', 0);
define('UDM_FIELD_CRC', 0);
define('UDM_FIELD_CATEGORY', 0);
define('UDM_FIELD_LANG', 0);
define('UDM_FIELD_CHARSET', 0);
define('UDM_PARAM_PAGE_SIZE', 0);
define('UDM_PARAM_PAGE_NUM', 0);
define('UDM_PARAM_SEARCH_MODE', 0);
define('UDM_PARAM_CACHE_MODE', 0);
define('UDM_PARAM_TRACK_MODE', 0);
define('UDM_PARAM_PHRASE_MODE', 0);
define('UDM_PARAM_CHARSET', 0);
define('UDM_PARAM_LOCAL_CHARSET', 0);
define('UDM_PARAM_BROWSER_CHARSET', 0);
define('UDM_PARAM_STOPTABLE', 0);
define('UDM_PARAM_STOP_TABLE', 0);
define('UDM_PARAM_STOPFILE', 0);
define('UDM_PARAM_STOP_FILE', 0);
define('UDM_PARAM_WEIGHT_FACTOR', 0);
define('UDM_PARAM_WORD_MATCH', 0);
define('UDM_PARAM_MAX_WORD_LEN', 0);
define('UDM_PARAM_MAX_WORDLEN', 0);
define('UDM_PARAM_MIN_WORD_LEN', 0);
define('UDM_PARAM_MIN_WORDLEN', 0);
define('UDM_PARAM_ISPELL_PREFIXES', 0);
define('UDM_PARAM_ISPELL_PREFIX', 0);
define('UDM_PARAM_PREFIXES', 0);
define('UDM_PARAM_PREFIX', 0);
define('UDM_PARAM_CROSS_WORDS', 0);
define('UDM_PARAM_CROSSWORDS', 0);
define('UDM_PARAM_VARDIR', 0);
define('UDM_PARAM_DATADIR', 0);
define('UDM_PARAM_HLBEG', 0);
define('UDM_PARAM_HLEND', 0);
define('UDM_PARAM_SYNONYM', 0);
define('UDM_PARAM_SEARCHD', 0);
define('UDM_PARAM_QSTRING', 0);
define('UDM_PARAM_REMOTE_ADDR', 0);
define('UDM_LIMIT_CAT', 0);
define('UDM_LIMIT_URL', 0);
define('UDM_LIMIT_TAG', 0);
define('UDM_LIMIT_LANG', 0);
define('UDM_LIMIT_DATE', 0);
define('UDM_PARAM_FOUND', 0);
define('UDM_PARAM_NUM_ROWS', 0);
define('UDM_PARAM_WORDINFO', 0);
define('UDM_PARAM_WORD_INFO', 0);
define('UDM_PARAM_SEARCHTIME', 0);
define('UDM_PARAM_SEARCH_TIME', 0);
define('UDM_PARAM_FIRST_DOC', 0);
define('UDM_PARAM_LAST_DOC', 0);
define('UDM_MODE_ALL', 0);
define('UDM_MODE_ANY', 0);
define('UDM_MODE_BOOL', 0);
define('UDM_MODE_PHRASE', 0);
define('UDM_CACHE_ENABLED', 0);
define('UDM_CACHE_DISABLED', 0);
define('UDM_TRACK_ENABLED', 0);
define('UDM_TRACK_DISABLED', 0);
define('UDM_PHRASE_ENABLED', 0);
define('UDM_PHRASE_DISABLED', 0);
define('UDM_CROSS_WORDS_ENABLED', 0);
define('UDM_CROSSWORDS_ENABLED', 0);
define('UDM_CROSS_WORDS_DISABLED', 0);
define('UDM_CROSSWORDS_DISABLED', 0);
define('UDM_PREFIXES_ENABLED', 0);
define('UDM_PREFIX_ENABLED', 0);
define('UDM_ISPELL_PREFIXES_ENABLED', 0);
define('UDM_ISPELL_PREFIX_ENABLED', 0);
define('UDM_PREFIXES_DISABLED', 0);
define('UDM_PREFIX_DISABLED', 0);
define('UDM_ISPELL_PREFIXES_DISABLED', 0);
define('UDM_ISPELL_PREFIX_DISABLED', 0);
define('UDM_ISPELL_TYPE_AFFIX', 0);
define('UDM_ISPELL_TYPE_SPELL', 0);
define('UDM_ISPELL_TYPE_DB', 0);
define('UDM_ISPELL_TYPE_SERVER', 0);
define('UDM_MATCH_WORD', 0);
define('UDM_MATCH_BEGIN', 0);
define('UDM_MATCH_SUBSTR', 0);
define('UDM_MATCH_END', 0);
define('MSQL_ASSOC', 0);
define('MSQL_NUM', 0);
define('MSQL_BOTH', 0);
define('MSSQL_ASSOC', 0);
define('MSSQL_NUM', 0);
define('MSSQL_BOTH', 0);
define('SQLTEXT', 0);
define('SQLVARCHAR', 0);
define('SQLCHAR', 0);
define('SQLINT1', 0);
define('SQLINT2', 0);
define('SQLINT4', 0);
define('SQLBIT', 0);
define('SQLFLT8', 0);
define('YPERR_ACCESS', 0);
define('YPERR_BADARGS', 0);
define('YPERR_BADDB', 0);
define('YPERR_BUSY', 0);
define('YPERR_DOMAIN', 0);
define('YPERR_KEY', 0);
define('YPERR_MAP', 0);
define('YPERR_NODOM', 0);
define('YPERR_NOMORE', 0);
define('YPERR_PMAP', 0);
define('YPERR_RESRC', 0);
define('YPERR_RPC', 0);
define('YPERR_YPBIND', 0);
define('YPERR_YPERR', 0);
define('YPERR_YPSERV', 0);
define('YPERR_VERS', 0);
define('OCI_DEFAULT', 0);
define('OCI_DESCRIBE_ONLY', 0);
define('OCI_COMMIT_ON_SUCCESS', 0);
define('OCI_EXACT_FETCH', 0);
define('OCI_SYSDATE', 0);
define('OCI_B_BFILE', 0);
define('OCI_B_CFILEE', 0);
define('OCI_B_CLOB', 0);
define('OCI_B_BLOB', 0);
define('OCI_B_ROWID', 0);
define('OCI_B_CURSOR', 0);
define('OCI_B_NTY', 0);
define('OCI_B_BIN', 0);
define('SQLT_BFILEE', 0);
define('SQLT_CFILEE', 0);
define('SQLT_CLOB', 0);
define('SQLT_BLOB', 0);
define('SQLT_RDD', 0);
define('SQLT_NTY', 0);
define('SQLT_LNG', 0);
define('SQLT_LBI', 0);
define('SQLT_BIN', 0);
define('SQLT_NUM', 0);
define('SQLT_INT', 0);
define('SQLT_AFC', 0);
define('SQLT_CHR', 0);
define('SQLT_VCS', 0);
define('SQLT_AVC', 0);
define('SQLT_STR', 0);
define('SQLT_LVC', 0);
define('SQLT_FLT', 0);
define('SQLT_ODT', 0);
define('SQLT_BDOUBLE', 0);
define('SQLT_BFLOAT', 0);
define('OCI_FETCHSTATEMENT_BY_COLUMN', 0);
define('OCI_FETCHSTATEMENT_BY_ROW', 0);
define('OCI_ASSOC', 0);
define('OCI_NUM', 0);
define('OCI_BOTH', 0);
define('OCI_RETURN_NULLS', 0);
define('OCI_RETURN_LOBS', 0);
define('OCI_DTYPE_FILE', 0);
define('OCI_DTYPE_LOB', 0);
define('OCI_DTYPE_ROWID', 0);
define('OCI_D_FILE', 0);
define('OCI_D_LOB', 0);
define('OCI_D_ROWID', 0);
define('OCI_SYSOPER', 0);
define('OCI_SYSDBA', 0);
define('OCI_LOB_BUFFER_FREE', 0);
define('OCI_TEMP_CLOB', 0);
define('OCI_TEMP_BLOB', 0);
define('ALC_FREQUENCY', 0);
define('ALC_REFRESH', 0);
define('ALC_SYNC', 0);
define('AL_FREQUENCY', 0);
define('AL_BITS', 0);
define('AL_CHANNELS', 0);
define('AL_SIZE', 0);
define('AL_BUFFER', 0);
define('AL_SOURCE_RELATIVE', 0);
define('AL_SOURCE_STATE', 0);
define('AL_PITCH', 0);
define('AL_GAIN', 0);
define('AL_MIN_GAIN', 0);
define('AL_MAX_GAIN', 0);
define('AL_MAX_DISTANCE', 0);
define('AL_ROLLOFF_FACTOR', 0);
define('AL_CONE_OUTER_GAIN', 0);
define('AL_CONE_INNER_ANGLE', 0);
define('AL_CONE_OUTER_ANGLE', 0);
define('AL_REFERENCE_DISTANCE', 0);
define('AL_POSITION', 0);
define('AL_VELOCITY', 0);
define('AL_DIRECTION', 0);
define('AL_ORIENTATION', 0);
define('AL_FORMAT_MONO8', 0);
define('AL_FORMAT_MONO16', 0);
define('AL_FORMAT_STEREO8', 0);
define('AL_FORMAT_STEREO16', 0);
define('AL_INITIAL', 0);
define('AL_PLAYING', 0);
define('AL_PAUSED', 0);
define('AL_STOPPED', 0);
define('AL_LOOPING', 0);
define('AL_TRUE', 0);
define('AL_FALSE', 0);
define('WNOHANG', 0);
define('WUNTRACED', 0);
define('SIG_IGN', 0);
define('SIG_DFL', 0);
define('SIG_ERR', 0);
define('SIGHUP', 0);
define('SIGINT', 0);
define('SIGQUIT', 0);
define('SIGILL', 0);
define('SIGTRAP', 0);
define('SIGABRT', 0);
define('SIGIOT', 0);
define('SIGBUS', 0);
define('SIGFPE', 0);
define('SIGKILL', 0);
define('SIGUSR1', 0);
define('SIGSEGV', 0);
define('SIGUSR2', 0);
define('SIGPIPE', 0);
define('SIGALRM', 0);
define('SIGTERM', 0);
define('SIGSTKFLT', 0);
define('SIGCLD', 0);
define('SIGCHLD', 0);
define('SIGCONT', 0);
define('SIGSTOP', 0);
define('SIGTSTP', 0);
define('SIGTTIN', 0);
define('SIGTTOU', 0);
define('SIGURG', 0);
define('SIGXCPU', 0);
define('SIGXFSZ', 0);
define('SIGVTALRM', 0);
define('SIGPROF', 0);
define('SIGWINCH', 0);
define('SIGPOLL', 0);
define('SIGIO', 0);
define('SIGPWR', 0);
define('SIGSYS', 0);
define('SIGBABY', 0);
define('PGSQL_ASSOC', 0);
define('PGSQL_NUM', 0);
define('PGSQL_BOTH', 0);
define('PGSQL_CONNECT_FORCE_NEW', 0);
define('PGSQL_CONNECTION_BAD', 0);
define('PGSQL_CONNECTION_OK', 0);
define('PGSQL_SEEK_SET', 0);
define('PGSQL_SEEK_CUR', 0);
define('PGSQL_SEEK_END', 0);
define('PGSQL_EMPTY_QUERY', 0);
define('PGSQL_COMMAND_OK', 0);
define('PGSQL_TUPLES_OK', 0);
define('PGSQL_COPY_OUT', 0);
define('PGSQL_COPY_IN', 0);
define('PGSQL_BAD_RESPONSE', 0);
define('PGSQL_NONFATAL_ERROR', 0);
define('PGSQL_FATAL_ERROR', 0);
define('PGSQL_TRANSACTION_IDLE', 0);
define('PGSQL_TRANSACTION_ACTIVE', 0);
define('PGSQL_TRANSACTION_INTRANS', 0);
define('PGSQL_TRANSACTION_INERROR', 0);
define('PGSQL_TRANSACTION_UNKNOWN', 0);
define('PGSQL_DIAG_SEVERITY', 0);
define('PGSQL_DIAG_SQLSTATE', 0);
define('PGSQL_DIAG_MESSAGE_PRIMARY', 0);
define('PGSQL_DIAG_MESSAGE_DETAIL', 0);
define('PGSQL_DIAG_MESSAGE_HINT', 0);
define('PGSQL_DIAG_STATEMENT_POSITION', 0);
define('PGSQL_DIAG_INTERNAL_POSITION', 0);
define('PGSQL_DIAG_INTERNAL_QUERY', 0);
define('PGSQL_DIAG_CONTEXT', 0);
define('PGSQL_DIAG_SOURCE_FILE', 0);
define('PGSQL_DIAG_SOURCE_LINE', 0);
define('PGSQL_DIAG_SOURCE_FUNCTION', 0);
define('PGSQL_ERRORS_TERSE', 0);
define('PGSQL_ERRORS_DEFAULT', 0);
define('PGSQL_ERRORS_VERBOSE', 0);
define('PGSQL_STATUS_LONG', 0);
define('PGSQL_STATUS_STRING', 0);
define('PGSQL_CONV_IGNORE_DEFAULT', 0);
define('PGSQL_CONV_FORCE_NULL', 0);
define('POSIX_F_OK', 0);
define('POSIX_R_OK', 0);
define('POSIX_W_OK', 0);
define('POSIX_X_OK', 0);
define('POSIX_S_IFBLK', 0);
define('POSIX_S_IFCHR', 0);
define('POSIX_S_IFIFO', 0);
define('POSIX_S_IFREG', 0);
define('POSIX_S_IFSOCK', 0);
define('PRINTER_COPIES', 0);
define('PRINTER_MODE', 0);
define('PRINTER_TITLE', 0);
define('PRINTER_DEVICENAME', 0);
define('PRINTER_DRIVERVERSION', 0);
define('PRINTER_OUTPUT_FILE', 0);
define('PRINTER_RESOLUTION_Y', 0);
define('PRINTER_RESOLUTION_X', 0);
define('PRINTER_SCALE', 0);
define('PRINTER_BACKGROUND_COLOR', 0);
define('PRINTER_PAPER_LENGTH', 0);
define('PRINTER_PAPER_WIDTH', 0);
define('PRINTER_PAPER_FORMAT', 0);
define('PRINTER_FORMAT_CUSTOM', 0);
define('PRINTER_FORMAT_LETTER', 0);
define('PRINTER_FORMAT_LEGAL', 0);
define('PRINTER_FORMAT_A3', 0);
define('PRINTER_FORMAT_A4', 0);
define('PRINTER_FORMAT_A5', 0);
define('PRINTER_FORMAT_B4', 0);
define('PRINTER_FORMAT_B5', 0);
define('PRINTER_FORMAT_FOLIO', 0);
define('PRINTER_ORIENTATION', 0);
define('PRINTER_ORIENTATION_PORTRAIT', 0);
define('PRINTER_ORIENTATION_LANDSCAPE', 0);
define('PRINTER_TEXT_COLOR', 0);
define('PRINTER_TEXT_ALIGN', 0);
define('PRINTER_TA_BASELINE', 0);
define('PRINTER_TA_BOTTOM', 0);
define('PRINTER_TA_TOP', 0);
define('PRINTER_TA_CENTER', 0);
define('PRINTER_TA_LEFT', 0);
define('PRINTER_TA_RIGHT', 0);
define('PRINTER_PEN_SOLID', 0);
define('PRINTER_PEN_DASH', 0);
define('PRINTER_PEN_DOT', 0);
define('PRINTER_PEN_DASHDOT', 0);
define('PRINTER_PEN_DASHDOTDOT', 0);
define('PRINTER_PEN_INVISIBLE', 0);
define('PRINTER_BRUSH_SOLID', 0);
define('PRINTER_BRUSH_CUSTOM', 0);
define('PRINTER_BRUSH_DIAGONAL', 0);
define('PRINTER_BRUSH_CROSS', 0);
define('PRINTER_BRUSH_DIAGCROSS', 0);
define('PRINTER_BRUSH_FDIAGONAL', 0);
define('PRINTER_BRUSH_HORIZONTAL', 0);
define('PRINTER_BRUSH_VERTICAL', 0);
define('PRINTER_FW_THIN', 0);
define('PRINTER_FW_ULTRALIGHT', 0);
define('PRINTER_FW_LIGHT', 0);
define('PRINTER_FW_NORMAL', 0);
define('PRINTER_FW_MEDIUM', 0);
define('PRINTER_FW_BOLD', 0);
define('PRINTER_FW_ULTRABOLD', 0);
define('PRINTER_FW_HEAVY', 0);
define('PRINTER_ENUM_LOCAL', 0);
define('PRINTER_ENUM_NAME', 0);
define('PRINTER_ENUM_SHARED', 0);
define('PRINTER_ENUM_DEFAULT', 0);
define('PRINTER_ENUM_CONNECTIONS', 0);
define('PRINTER_ENUM_NETWORK', 0);
define('PRINTER_ENUM_REMOTE', 0);
define('PSPELL_FAST', 0);
define('PSPELL_NORMAL', 0);
define('PSPELL_BAD_SPELLERS', 0);
define('PSPELL_RUN_TOGETHER', 0);
define('RAR_HOST_MSDOS', 0);
define('RAR_HOST_OS2', 0);
define('RAR_HOST_WIN32', 0);
define('RAR_HOST_UNIX', 0);
define('RAR_HOST_BEOS', 0);
define('RUNKIT_IMPORT_FUNCTIONS', 0);
define('RUNKIT_IMPORT_CLASS_METHODS', 0);
define('RUNKIT_IMPORT_CLASS_CONSTS', 0);
define('RUNKIT_IMPORT_CLASS_PROPS', 0);
define('RUNKIT_IMPORT_CLASSES', 0);
define('RUNKIT_IMPORT_OVERRIDE', 0);
define('RUNKIT_ACC_PUBLIC', 0);
define('RUNKIT_ACC_PROTECTED', 0);
define('RUNKIT_ACC_PRIVATE', 0);
define('CLASSKIT_ACC_PUBLIC', 0);
define('CLASSKIT_ACC_PROTECTED', 0);
define('CLASSKIT_ACC_PRIVATE', 0);
define('CLASSKIT_AGGREGATE_OVERRIDE', 0);
define('RUNKIT_VERSION', '');
define('CLASSKIT_VERSION', '');
define('SAM_AUTO', '');
define('SAM_BOOLEAN', '');
define('SAM_BUS', '');
define('SAM_BYTE', '');
define('SAM_BYTES', '');
define('SAM_CORRELID', '');
define('SAM_DELIVERYMODE', '');
define('SAM_DOUBLE', '');
define('SAM_ENDPOINTS', '');
define('SAM_FLOAT', '');
define('SAM_HOST', '');
define('SAM_INT', '');
define('SAM_LONG', '');
define('SAM_MANUAL', '');
define('SAM_MESSAGEID', '');
define('SAM_MQTT', '');
define('SAM_MQTT_CLEANSTART', false);
define('SAM_NON_PERSISTENT', '');
define('SAM_PASSWORD', '');
define('SAM_PERSISTENT', '');
define('SAM_PORT', '');
define('SAM_PRIORITY', '');
define('SAM_REPLY_TO', '');
define('SAM_RTT', '');
define('SAM_STRING', '');
define('SAM_TARGETCHAIN', '');
define('SAM_TEXT', '');
define('SAM_TIMETOLIVE', '');
define('SAM_TRANSACTIONS', '');
define('SAM_USERID', '');
define('SAM_WAIT', '');
define('SAM_WMQ', '');
define('SAM_WMQ_BINDINGS', '');
define('SAM_WMQ_CLIENT', '');
define('SAM_WMQ_TARGET_CLIENT', '');
define('SAM_WPM', '');
define('SID', '');
define('SNMP_OID_OUTPUT_FULL', 0);
define('SNMP_OID_OUTPUT_NUMERIC', 0);
define('SNMP_VALUE_LIBRARY', 0);
define('SNMP_VALUE_PLAIN', 0);
define('SNMP_VALUE_OBJECT', 0);
define('SNMP_BIT_STR', 0);
define('SNMP_OCTET_STR', 0);
define('SNMP_OPAQUE', 0);
define('SNMP_NULL', 0);
define('SNMP_OBJECT_ID', 0);
define('SNMP_IPADDRESS', 0);
define('SNMP_COUNTER', 0);
define('SNMP_UNSIGNED', 0);
define('SNMP_TIMETICKS', 0);
define('SNMP_UINTEGER', 0);
define('SNMP_INTEGER', 0);
define('SNMP_COUNTER64', 0);
define('SOAP_1_1', 0);
define('SOAP_1_2', 0);
define('SOAP_PERSISTENCE_SESSION', 0);
define('SOAP_PERSISTENCE_REQUEST', 0);
define('SOAP_FUNCTIONS_ALL', 0);
define('SOAP_ENCODED', 0);
define('SOAP_LITERAL', 0);
define('SOAP_RPC', 0);
define('SOAP_DOCUMENT', 0);
define('SOAP_ACTOR_NEXT', 0);
define('SOAP_ACTOR_NONE', 0);
define('SOAP_ACTOR_UNLIMATERECEIVER', 0);
define('SOAP_COMPRESSION_ACCEPT', 0);
define('SOAP_COMPRESSION_GZIP', 0);
define('SOAP_COMPRESSION_DEFLATE', 0);
define('SOAP_WAIT_ONE_WAY_CALLS', 0);
define('UNKNOWN_TYPE', 0);
define('XSD_STRING', 0);
define('XSD_BOOLEAN', 0);
define('XSD_DECIMAL', 0);
define('XSD_FLOAT', 0);
define('XSD_DOUBLE', 0);
define('XSD_DURATION', 0);
define('XSD_DATETIME', 0);
define('XSD_TIME', 0);
define('XSD_DATE', 0);
define('XSD_GYEARMONTH', 0);
define('XSD_GYEAR', 0);
define('XSD_GMONTHDAY', 0);
define('XSD_GDAY', 0);
define('XSD_GMONTH', 0);
define('XSD_HEXBINARY', 0);
define('XSD_BASE64BINARY', 0);
define('XSD_ANYURI', 0);
define('XSD_ANYXML', 0);
define('XSD_QNAME', 0);
define('XSD_NOTATION', 0);
define('XSD_NORMALIZEDSTRING', 0);
define('XSD_TOKEN', 0);
define('XSD_LANGUAGE', 0);
define('XSD_NMTOKEN', 0);
define('XSD_NAME', 0);
define('XSD_NCNAME', 0);
define('XSD_ID', 0);
define('XSD_IDREF', 0);
define('XSD_IDREFS', 0);
define('XSD_ENTITY', 0);
define('XSD_ENTITIES', 0);
define('XSD_INTEGER', 0);
define('XSD_NONPOSITIVEINTEGER', 0);
define('XSD_NEGATIVEINTEGER', 0);
define('XSD_LONG', 0);
define('XSD_INT', 0);
define('XSD_SHORT', 0);
define('XSD_BYTE', 0);
define('XSD_NONNEGATIVEINTEGER', 0);
define('XSD_UNSIGNEDLONG', 0);
define('XSD_UNSIGNEDINT', 0);
define('XSD_UNSIGNEDSHORT', 0);
define('XSD_UNSIGNEDBYTE', 0);
define('XSD_POSITIVEINTEGER', 0);
define('XSD_NMTOKENS', 0);
define('XSD_ANYTYPE', 0);
define('SOAP_ENC_OBJECT', 0);
define('SOAP_ENC_ARRAY', 0);
define('XSD_1999_TIMEINSTANT', 0);
define('XSD_NAMESPACE', '');
define('XSD_1999_NAMESPACE', '');
define('WSDL_CACHE_NONE', 0);
define('WSDL_CACHE_DISK', 0);
define('WSDL_CACHE_MEMORY', 0);
define('WSDL_CACHE_BOTH', 0);
define('AF_UNIX', 0);
define('AF_INET', 0);
define('AF_INET6', 0);
define('SOCK_STREAM', 0);
define('SOCK_DGRAM', 0);
define('SOCK_RAW', 0);
define('SOCK_SEQPACKET', 0);
define('SOCK_RDM', 0);
define('MSG_OOB', 0);
define('MSG_WAITALL', 0);
define('MSG_PEEK', 0);
define('MSG_DONTROUTE', 0);
define('MSG_EOR', 0);
define('MSG_EOF', 0);
define('SO_DEBUG', 0);
define('SO_REUSEADDR', 0);
define('SO_KEEPALIVE', 0);
define('SO_DONTROUTE', 0);
define('SO_LINGER', 0);
define('SO_BROADCAST', 0);
define('SO_OOBINLINE', 0);
define('SO_SNDBUF', 0);
define('SO_RCVBUF', 0);
define('SO_SNDLOWAT', 0);
define('SO_RCVLOWAT', 0);
define('SO_SNDTIMEO', 0);
define('SO_RCVTIMEO', 0);
define('SO_TYPE', 0);
define('SO_ERROR', 0);
define('SOL_SOCKET', 0);
define('PHP_NORMAL_READ', 0);
define('PHP_BINARY_READ', 0);
define('SOL_TCP', 0);
define('SOL_UDP', 0);
define('SQLITE_ASSOC', 0);
define('SQLITE_BOTH', 0);
define('SQLITE_NUM', 0);
define('SSH2_FINGERPRINT_MD5', 0);
define('SSH2_FINGERPRINT_SHA1', 0);
define('SSH2_FINGERPRINT_HEX', 0);
define('SSH2_FINGERPRINT_RAW', 0);
define('SSH2_TERM_UNIT_CHARS', 0);
define('SSH2_TERM_UNIT_PIXELS', 0);
define('SSH2_DEFAULT_TERM_WIDTH', 0);
define('SSH2_DEFAULT_TERM_HEIGHT', 0);
define('SSH2_DEFAULT_TERM_UNIT', 0);
define('SSH2_STREAM_STDIO', 0);
define('SSH2_STREAM_STDERR', 0);
define('SSH2_DEFAULT_TERMINAL', '');
define('CRYPT_SALT_LENGTH', 0);
define('CRYPT_STD_DES', 0);
define('CRYPT_EXT_DES', 0);
define('CRYPT_MD5', 0);
define('CRYPT_BLOWFISH', 0);
define('HTML_SPECIALCHARS', 0);
define('HTML_ENTITIES', 0);
define('ENT_COMPAT', 0);
define('ENT_QUOTES', 0);
define('ENT_NOQUOTES', 0);
define('CHAR_MAX', 0);
define('LC_CTYPE', 0);
define('LC_NUMERIC', 0);
define('LC_TIME', 0);
define('LC_COLLATE', 0);
define('LC_MONETARY', 0);
define('LC_ALL', 0);
define('LC_MESSAGES', 0);
define('STR_PAD_LEFT', 0);
define('STR_PAD_RIGHT', 0);
define('STR_PAD_BOTH', 0);
define('SVN_REVISON_HEAD', 0);
define('MOD_COLOR', 0);
define('MOD_MATRIX', 0);
define('TYPE_PUSHBUTTON', 0);
define('TYPE_MENUBUTTON', 0);
define('BSHitTest', 0.0);
define('BSDown', 0.0);
define('BSOver', 0.0);
define('BSUp', 0.0);
define('OverDowntoIdle', 0);
define('IdletoOverDown', 0);
define('OutDowntoIdle', 0);
define('OutDowntoOverDown', 0);
define('OverDowntoOutDown', 0);
define('OverUptoOverDown', 0);
define('OverUptoIdle', 0);
define('IdletoOverUp', 0);
define('ButtonEnter', 0);
define('ButtonExit', 0);
define('MenuEnter', 0);
define('MenuExit', 0);
define('ODBC_TYPE', 0);
define('ODBC_BINMODE_PASSTHRU', 0);
define('ODBC_BINMODE_RETURN', 0);
define('ODBC_BINMODE_CONVERT', 0);
define('SQL_ODBC_CURSORS', 0);
define('SQL_CUR_USE_DRIVER', 0);
define('SQL_CUR_USE_IF_NEEDED', 0);
define('SQL_CUR_USE_ODBC', 0);
define('SQL_CONCURRENCY', 0);
define('SQL_CONCUR_READ_ONLY', 0);
define('SQL_CONCUR_LOCK', 0);
define('SQL_CONCUR_ROWVER', 0);
define('SQL_CONCUR_VALUES', 0);
define('SQL_CURSOR_TYPE', 0);
define('SQL_CURSOR_FORWARD_ONLY', 0);
define('SQL_CURSOR_KEYSET_DRIVEN', 0);
define('SQL_CURSOR_DYNAMIC', 0);
define('SQL_CURSOR_STATIC', 0);
define('SQL_KEYSET_SIZE', 0);
define('SQL_CHAR', 0);
define('SQL_VARCHAR', 0);
define('SQL_LONGVARCHAR', 0);
define('SQL_DECIMAL', 0);
define('SQL_NUMERIC', 0);
define('SQL_BIT', 0);
define('SQL_TINYINT', 0);
define('SQL_SMALLINT', 0);
define('SQL_INTEGER', 0);
define('SQL_BIGINT', 0);
define('SQL_REAL', 0);
define('SQL_FLOAT', 0);
define('SQL_DOUBLE', 0);
define('SQL_BINARY', 0);
define('SQL_VARBINARY', 0);
define('SQL_LONGVARBINARY', 0);
define('SQL_DATE', 0);
define('SQL_TIME', 0);
define('SQL_TIMESTAMP', 0);
define('SQL_TYPE_DATE', 0);
define('SQL_TYPE_TIME', 0);
define('SQL_TYPE_TIMESTAMP', 0);
define('SQL_BEST_ROWID', 0);
define('SQL_ROWVER', 0);
define('SQL_SCOPE_CURROW', 0);
define('SQL_SCOPE_TRANSACTION', 0);
define('SQL_SCOPE_SESSION', 0);
define('SQL_NO_NULLS', 0);
define('SQL_NULLABLE', 0);
define('SQL_INDEX_UNIQUE', 0);
define('SQL_INDEX_ALL', 0);
define('SQL_ENSURE', 0);
define('SQL_QUICK', 0);
define('PHP_URL_SCHEME', 0);
define('PHP_URL_HOST', 0);
define('PHP_URL_PORT', 0);
define('PHP_URL_USER', 0);
define('PHP_URL_PASS', 0);
define('PHP_URL_PATH', 0);
define('PHP_URL_QUERY', 0);
define('PHP_URL_FRAGMENT', 0);
define('DC_MICROSOFT', 0);
define('DC_BORLAND', 0);
define('DC_CALL_CDECL', 0);
define('DC_CALL_STD', 0);
define('DC_RETVAL_MATH4', 0);
define('DC_RETVAL_MATH8', 0);
define('DC_CALL_STD_BO', 0);
define('DC_CALL_STD_MS', 0);
define('DC_CALL_STD_M8', 0);
define('DC_FLAG_ARGPTR', 0);
define('WIN32_SERVICE_CONTROL_CONTINUE', 0);
define('WIN32_SERVICE_CONTROL_INTERROGATE', 0);
define('WIN32_SERVICE_CONTROL_PAUSE', 0);
define('WIN32_SERVICE_CONTROL_STOP', 0);
define('WIN32_SERVICE_CONTROL_HARDWAREPROFILECHANGE', 0);
define('WIN32_SERVICE_CONTROL_POWEREVENT', 0);
define('WIN32_SERVICE_CONTROL_SESSIONCHANGE', 0);
define('WIN32_ERROR_CALL_NOT_IMPLEMENTED', 0);
define('WIN32_NO_ERROR', 0);
define('WIN32_SERVICE_RUNNING', 0);
define('WIN32_SERVICE_STOPPED', 0);
define('WIN32_SERVICE_STOP_PENDING', 0);
define('WIN32_SERVICE_WIN32_OWN_PROCESS', 0);
define('WIN32_SERVICE_INTERACTIVE_PROCESS', 0);
define('WIN32_SERVICE_START_PENDING', 0);
define('WIN32_SERVICE_CONTINUE_PENDING', 0);
define('WIN32_SERVICE_PAUSE_PENDING', 0);
define('WIN32_SERVICE_PAUSED', 0);
define('WIN32_SERVICE_ACCEPT_NETBINDCHANGE', 0);
define('WIN32_SERVICE_ACCEPT_PARAMCHANGE', 0);
define('WIN32_SERVICE_ACCEPT_PAUSE_CONTINUE', 0);
define('WIN32_SERVICE_ACCEPT_SHUTDOWN', 0);
define('WIN32_SERVICE_ACCEPT_STOP', 0);
define('WIN32_SERVICE_ACCEPT_HARDWAREPROFILECHANGE', 0);
define('WIN32_SERVICE_ACCEPT_POWEREVENT', 0);
define('WIN32_SERVICE_ACCEPT_SESSIONCHANGE', 0);
define('WIN32_SERVICE_FILE_SYSTEM_DRIVER', 0);
define('WIN32_SERVICE_KERNEL_DRIVER', 0);
define('WIN32_SERVICE_WIN32_SHARE_PROCESS', 0);
define('WIN32_SERVICE_RUNS_IN_SYSTEM_PROCESS', 0);
define('XATTR_ROOT', 0);
define('XATTR_DONTFOLLOW', 0);
define('XATTR_CREATE', 0);
define('XATTR_REPLACE', 0);
define('XDIFF_PATCH_NORMAL', 0);
define('XDIFF_PATCH_REVERSE', 0);
define('XML_ERROR_NONE', 0);
define('XML_ERROR_NO_MEMORY', 0);
define('XML_ERROR_SYNTAX', 0);
define('XML_ERROR_NO_ELEMENTS', 0);
define('XML_ERROR_INVALID_TOKEN', 0);
define('XML_ERROR_UNCLOSED_TOKEN', 0);
define('XML_ERROR_PARTIAL_CHAR', 0);
define('XML_ERROR_TAG_MISMATCH', 0);
define('XML_ERROR_DUPLICATE_ATTRIBUTE', 0);
define('XML_ERROR_JUNK_AFTER_DOC_ELEMENT', 0);
define('XML_ERROR_PARAM_ENTITY_REF', 0);
define('XML_ERROR_UNDEFINED_ENTITY', 0);
define('XML_ERROR_RECURSIVE_ENTITY_REF', 0);
define('XML_ERROR_ASYNC_ENTITY', 0);
define('XML_ERROR_BAD_CHAR_REF', 0);
define('XML_ERROR_BINARY_ENTITY_REF', 0);
define('XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF', 0);
define('XML_ERROR_MISPLACED_XML_PI', 0);
define('XML_ERROR_UNKNOWN_ENCODING', 0);
define('XML_ERROR_INCORRECT_ENCODING', 0);
define('XML_ERROR_UNCLOSED_CDATA_SECTION', 0);
define('XML_ERROR_EXTERNAL_ENTITY_HANDLING', 0);
define('XML_OPTION_CASE_FOLDING', 0);
define('XML_OPTION_TARGET_ENCODING', 0);
define('XML_OPTION_SKIP_TAGSTART', 0);
define('XML_OPTION_SKIP_WHITE', 0);
define('XSL_CLONE_AUTO', 0);
define('XSL_CLONE_NEVER', 0);
define('XSL_CLONE_ALWAYS', 0);
define('LIBXSLT_VERSION', 0);
define('LIBXSLT_DOTTED_VERSION', '');
define('LIBEXSLT_VERSION', 0);
define('LIBEXSLT_DOTTED_VERSION', '');
define('XSLT_OPT_SILENT', 0);
define('XSLT_SABOPT_PARSE_PUBLIC_ENTITIES', 0);
define('XSLT_SABOPT_DISABLE_ADDING_META', 0);
define('XSLT_SABOPT_DISABLE_STRIPPING', 0);
define('XSLT_SABOPT_IGNORE_DOC_NOT_FOUND', 0);
define('XSLT_SABOPT_FILES_TO_HANDLER', 0);
define('XSLT_ERR_UNSUPPORTED_SCHEME', 0);
define('FORCE_GZIP', 0);
define('FORCE_DEFLATE', 0);
define('PHP_VERSION', '');
define('PHP_MAJOR_VERSION', 0);
define('PHP_MINOR_VERSION', 0);
define('PHP_RELEASE_VERSION', 0);
define('PHP_VERSION_ID', 0);
define('PHP_EXTRA_VERSION', '');
define('PHP_ZTS', 0);
define('PHP_DEBUG', 0);
define('PHP_OS', '');
define('PHP_SAPI', '');
define('PHP_EOL', '');
define('PHP_INT_MAX', 0);
define('PHP_INT_SIZE', 0);
define('DEFAULT_INCLUDE_PATH', '');
define('PEAR_INSTALL_DIR', '');
define('PEAR_EXTENSION_DIR', '');
define('PHP_EXTENSION_DIR', '');
define('PHP_PREFIX', '');
define('PHP_BINDIR', '');
define('PHP_LIBDIR', '');
define('PHP_DATADIR', '');
define('PHP_SYSCONFDIR', '');
define('PHP_LOCALSTATEDIR', '');
define('PHP_CONFIG_FILE_PATH', '');
define('PHP_CONFIG_FILE_SCAN_DIR', '');
define('PHP_SHLIB_SUFFIX', '');
define('PHP_OUTPUT_HANDLER_START', 0);
define('PHP_OUTPUT_HANDLER_CONT', 0);
define('PHP_OUTPUT_HANDLER_END', 0);
define('E_ERROR', 0);
define('E_WARNING', 0);
define('E_PARSE', 0);
define('E_NOTICE', 0);
define('E_CORE_ERROR', 0);
define('E_CORE_WARNING', 0);
define('E_COMPILE_ERROR', 0);
define('E_COMPILE_WARNING', 0);
define('E_USER_ERROR', 0);
define('E_USER_WARNING', 0);
define('E_USER_NOTICE', 0);
define('E_ALL', 0);
define('E_STRICT', 0);
define('SORT_ASC', 0);
define('SORT_DESC', 0);
define('SORT_REGULAR', 0);
define('SORT_NUMERIC', 0);
define('SORT_STRING', 0);
define('CASE_LOWER', 0);
define('CASE_UPPER', 0);
define('INI_USER', 0);
define('INI_PERDIR', 0);
define('INI_SYSTEM', 0);
define('INI_ALL', 0);
define('M_E', 0.0);
define('M_LOG2E', 0.0);
define('M_LOG10E', 0.0);
define('M_LN2', 0.0);
define('M_LN10', 0.0);
define('M_PI', 0.0);
define('M_PI_2', 0.0);
define('M_PI_4', 0.0);
define('M_1_PI', 0.0);
define('M_2_PI', 0.0);
define('M_2_SQRTPI', 0.0);
define('M_SQRT2', 0.0);
define('M_SQRT1_2', 0.0);
define('SEEK_SET', 0);
define('SEEK_CUR', 0);
define('SEEK_END', 0);
define('LOCK_SH', 0);
define('LOCK_EX', 0);
define('LOCK_UN', 0);
define('LOCK_NB', 0);
define('INFO_GENERAL', 0);
define('INFO_CREDITS', 0);
define('INFO_CONFIGURATION', 0);
define('INFO_MODULES', 0);
define('INFO_ENVIRONMENT', 0);
define('INFO_VARIABLES', 0);
define('INFO_LICENSE', 0);
define('INFO_ALL', 0);
define('CREDITS_GROUP', 0);
define('CREDITS_GENERAL', 0);
define('CREDITS_SAPI', 0);
define('CREDITS_MODULES', 0);
define('CREDITS_DOCS', 0);
define('CREDITS_FULLPAGE', 0);
define('CREDITS_QA', 0);
define('CREDITS_ALL', 0);
define('ABDAY_1', 0);
define('ABDAY_2', 0);
define('ABDAY_3', 0);
define('ABDAY_4', 0);
define('ABDAY_5', 0);
define('ABDAY_6', 0);
define('ABDAY_7', 0);
define('DAY_1', 0);
define('DAY_2', 0);
define('DAY_3', 0);
define('DAY_4', 0);
define('DAY_5', 0);
define('DAY_6', 0);
define('DAY_7', 0);
define('ABMON_1', 0);
define('ABMON_2', 0);
define('ABMON_3', 0);
define('ABMON_4', 0);
define('ABMON_5', 0);
define('ABMON_6', 0);
define('ABMON_7', 0);
define('ABMON_8', 0);
define('ABMON_9', 0);
define('ABMON_10', 0);
define('ABMON_11', 0);
define('ABMON_12', 0);
define('MON_1', 0);
define('MON_2', 0);
define('MON_3', 0);
define('MON_4', 0);
define('MON_5', 0);
define('MON_6', 0);
define('MON_7', 0);
define('MON_8', 0);
define('MON_9', 0);
define('MON_10', 0);
define('MON_11', 0);
define('MON_12', 0);
define('AM_STR', 0);
define('PM_STR', 0);
define('D_T_FMT', 0);
define('D_FMT', 0);
define('T_FMT', 0);
define('T_FMT_AMPM', 0);
define('ERA', 0);
define('ERA_YEAR', 0);
define('ERA_D_T_FMT', 0);
define('ERA_D_FMT', 0);
define('ERA_T_FMT', 0);
define('ALT_DIGITS', 0);
define('INT_CURR_SYMBOL', 0);
define('CURRENCY_SYMBOL', 0);
define('CRNCYSTR', 0);
define('MON_DECIMAL_POINT', 0);
define('MON_THOUSANDS_SEP', 0);
define('MON_GROUPING', 0);
define('POSITIVE_SIGN', 0);
define('NEGATIVE_SIGN', 0);
define('INT_FRAC_DIGITS', 0);
define('FRAC_DIGITS', 0);
define('P_CS_PRECEDES', 0);
define('P_SEP_BY_SPACE', 0);
define('N_CS_PRECEDES', 0);
define('N_SEP_BY_SPACE', 0);
define('P_SIGN_POSN', 0);
define('N_SIGN_POSN', 0);
define('DECIMAL_POINT', 0);
define('RADIXCHAR', 0);
define('THOUSANDS_SEP', 0);
define('THOUSEP', 0);
define('GROUPING', 0);
define('YESEXPR', 0);
define('NOEXPR', 0);
define('YESSTR', 0);
define('NOSTR', 0);
define('CODESET', 0);
define('LOG_EMERG', 0);
define('LOG_ALERT', 0);
define('LOG_CRIT', 0);
define('LOG_ERR', 0);
define('LOG_WARNING', 0);
define('LOG_NOTICE', 0);
define('LOG_INFO', 0);
define('LOG_DEBUG', 0);
define('LOG_KERN', 0);
define('LOG_USER', 0);
define('LOG_MAIL', 0);
define('LOG_DAEMON', 0);
define('LOG_AUTH', 0);
define('LOG_SYSLOG', 0);
define('LOG_LPR', 0);
define('LOG_NEWS', 0);
define('LOG_UUCP', 0);
define('LOG_CRON', 0);
define('LOG_AUTHPRIV', 0);
define('LOG_LOCAL0', 0);
define('LOG_LOCAL1', 0);
define('LOG_LOCAL2', 0);
define('LOG_LOCAL3', 0);
define('LOG_LOCAL4', 0);
define('LOG_LOCAL5', 0);
define('LOG_LOCAL6', 0);
define('LOG_LOCAL7', 0);
define('LOG_PID', 0);
define('LOG_CONS', 0);
define('LOG_ODELAY', 0);
define('LOG_NDELAY', 0);
define('LOG_NOWAIT', 0);
define('LOG_PERROR', 0);
