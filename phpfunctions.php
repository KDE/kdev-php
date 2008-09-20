<?php
// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

function ts_allocate_id($rsrc_id, $size, $ctor, $dtor) {}
function ts_free_id($id) {}
function ts_free_thread($void) {}
function ts_resource($id) {}
function ts_resource_ex($id, $th_id) {}
function tsrm_error($level, $format) {}
function tsrm_error_set($level, $debug_filename) {}
function tsrm_free_interpreter_context($context) {}
function tsrm_mutex_alloc($void) {}
function tsrm_mutex_free($mutexp) {}
function tsrm_mutex_lock($mutexp) {}
function tsrm_mutex_unlock($mutexp) {}
function tsrm_new_interpreter_context($void) {}
function tsrm_set_interpreter_context($new_ctx) {}
function tsrm_set_new_thread_begin_handler($new_thread_begin_handler) {}
function tsrm_set_new_thread_end_handler($new_thread_end_handler) {}
function tsrm_shutdown($void) {}
function tsrm_startup($expected_threads, $expected_resources, $debug_level, $debug_filename) {}
function tsrm_thread_id($void) {}
function virtual_access($pathname, $mode, $TSRMLS_DC) {}
function virtual_chdir($path, $TSRMLS_DC) {}
function virtual_chdir_file($path, $chdir_func, $TSRMLS_DC) {}
function virtual_chmod($filename, $mode, $TSRMLS_DC) {}
function virtual_chown($filename, $owner, $group, $link, $TSRMLS_DC) {}
function virtual_creat($path, $mode, $TSRMLS_DC) {}
function virtual_cwd_shutdown($void) {}
function virtual_cwd_startup($void) {}
function virtual_file_ex($state, $path, $verify_path, $use_realpath) {}
function virtual_filepath($path, $filepath, $TSRMLS_DC) {}
function virtual_filepath_ex($path, $filepath, $verify_path, $TSRMLS_DC) {}
function virtual_fopen($path, $mode, $TSRMLS_DC) {}
function virtual_getcwd($buf, $size, $TSRMLS_DC) {}
function virtual_getcwd_ex($length, $TSRMLS_DC) {}
function virtual_lstat($path, $buf, $TSRMLS_DC) {}
function virtual_mkdir($pathname, $mode, $TSRMLS_DC) {}
function virtual_open($path, $TSRMLS_DC, $flags) {}
function virtual_opendir($pathname, $TSRMLS_DC) {}
function virtual_popen($command, $type, $TSRMLS_DC) {}
function virtual_realpath($path, $real_path, $TSRMLS_DC) {}
function virtual_rename($oldname, $newname, $TSRMLS_DC) {}
function virtual_rmdir($pathname, $TSRMLS_DC) {}
function virtual_stat($path, $buf, $TSRMLS_DC) {}
function virtual_unlink($path, $TSRMLS_DC) {}
function virtual_utime($filename, $buf, $TSRMLS_DC) {}
function VCWD_ACCESS($pathname, $mode) {}
function VCWD_CHDIR($path) {}
function VCWD_CHDIR_FILE($path) {}
function VCWD_CHMOD($path, $mode) {}
function VCWD_CHOWN($path, $owner, $group) {}
function VCWD_CREAT($path, $mode) {}
function VCWD_FOPEN($path, $mode) {}
function VCWD_GETCWD($buff, $size) {}
function VCWD_GETWD($buf) {}
function VCWD_LCHOWN($path, $owner, $group) {}
function VCWD_LSTAT($path, $buff) {}
function VCWD_MKDIR($pathname, $mode) {}
function VCWD_OPEN($path, $flags) {}
function VCWD_OPEN_MODE($path, $flags, $mode) {}
function VCWD_OPENDIR($pathname) {}
function VCWD_POPEN($command, $type) {}
function VCWD_REALPATH($path, $real_path) {}
function VCWD_RENAME($oldname, $newname) {}
function VCWD_RMDIR($pathname) {}
function VCWD_STAT($path, $buff) {}
function VCWD_UNLINK($path) {}
function VCWD_UTIME($path, $time) {}
function add_assoc_bool($arg, $key, $b) {}
function add_assoc_bool_ex($arg, $key, $key_len, $b) {}
function add_assoc_double($arg, $key, $d) {}
function add_assoc_double_ex($arg, $key, $key_len, $d) {}
function add_assoc_function($arg, $key, $(*function_ptr)(INTERNAL_FUNCTION_PARAMETERS)) {}
function add_assoc_long($arg, $key, $n) {}
function add_assoc_long_ex($arg, $key, $key_len, $n) {}
function add_assoc_null($arg, $key) {}
function add_assoc_null_ex($arg, $key, $key_len) {}
function add_assoc_resource($arg, $key, $r) {}
function add_assoc_resource_ex($arg, $key, $key_len, $r) {}
function add_assoc_string($arg, $key, $str, $duplicate) {}
function add_assoc_string_ex($arg, $key, $key_len, $str, $duplicate) {}
function add_assoc_stringl($arg, $key, $str, $length, $duplicate) {}
function add_assoc_stringl_ex($arg, $key, $key_len, $str, $length, $duplicate) {}
function add_assoc_unicode($arg, $key, $str, $duplicate) {}
function add_assoc_unicode_ex($arg, $key, $key_len, $str, $duplicate) {}
function add_assoc_unicodel($arg, $key, $str, $length, $duplicate) {}
function add_assoc_unicodel_ex($arg, $key, $key_len, $str, $length, $duplicate) {}
function add_assoc_unset($arg, $key) {}
function add_assoc_zval($arg, $key, $value) {}
function add_assoc_zval_ex($arg, $key, $key_len, $value) {}
function add_get_assoc_string($arg, $key, $str, $dest, $duplicate) {}
function add_get_assoc_string_ex($arg, $key, $key_len, $str, $dest, $duplicate) {}
function add_get_assoc_stringl($arg, $key, $str, $length, $dest, $duplicate) {}
function add_get_assoc_stringl_ex($arg, $key, $key_len, $str, $length, $dest, $duplicate) {}
function add_get_index_binary($arg, $idx, $str, $dest, $duplicate) {}
function add_get_index_binaryl($arg, $idx, $str, $length, $dest, $duplicate) {}
function add_get_index_double($arg, $idx, $d, $dest) {}
function add_get_index_long($arg, $idx, $l, $dest) {}
function add_get_index_string($arg, $idx, $str, $dest, $duplicate) {}
function add_get_index_stringl($arg, $idx, $str, $length, $dest, $duplicate) {}
function add_get_index_unicode($arg, $idx, $str, $dest, $duplicate) {}
function add_get_index_unicodel($arg, $idx, $str, $length, $dest, $duplicate) {}
function add_index_binary($arg, $idx, $str, $duplicate, $TSRMLS_DC) {}
function add_index_binaryl($arg, $idx, $str, $length, $duplicate, $TSRMLS_DC) {}
function add_index_bool($arg, $idx, $b) {}
function add_index_double($arg, $idx, $d) {}
function add_index_long($arg, $idx, $n) {}
function add_index_null($arg, $idx) {}
function add_index_resource($arg, $idx, $r) {}
function add_index_string($arg, $idx, $str, $duplicate) {}
function add_index_stringl($arg, $idx, $str, $length, $duplicate) {}
function add_index_unicode($arg, $idx, $str, $duplicate) {}
function add_index_unicodel($arg, $idx, $str, $length, $duplicate) {}
function add_index_unset($arg, $key) {}
function add_index_zval($arg, $index, $value) {}
function add_method($arg, $key, $method) {}
function add_next_index_binary($arg, $str, $duplicate) {}
function add_next_index_binaryl($arg, $str, $length, $duplicate) {}
function add_next_index_bool($arg, $b) {}
function add_next_index_double($arg, $d) {}
function add_next_index_long($arg, $n) {}
function add_next_index_null($arg) {}
function add_next_index_resource($arg, $r) {}
function add_next_index_string($arg, $str, $duplicate) {}
function add_next_index_stringl($arg, $str, $length, $duplicate) {}
function add_next_index_unicode($arg, $str, $duplicate) {}
function add_next_index_unicodel($arg, $str, $length, $duplicate) {}
function add_next_index_unset($arg) {}
function add_next_index_zval($arg, $value) {}
function add_property_ascii_string($arg, $key, $str, $duplicate) {}
function add_property_ascii_string_ex($arg, $key, $key_len, $str, $duplicate, $TSRMLS_DC) {}
function add_property_ascii_stringl($arg, $key, $str, $length, $duplicate) {}
function add_property_ascii_stringl_ex($arg, $key, $key_len, $str, $length, $duplicate, $TSRMLS_DC) {}
function add_property_bool($arg, $key, $b) {}
function add_property_bool_ex($arg, $key, $key_len, $b, $TSRMLS_DC) {}
function add_property_double($arg, $key, $d) {}
function add_property_double_ex($arg, $key, $key_len, $d, $TSRMLS_DC) {}
function add_property_long($arg, $key, $n) {}
function add_property_long_ex($arg, $key, $key_len, $l, $TSRMLS_DC) {}
function add_property_null($arg, $key) {}
function add_property_null_ex($arg, $key, $key_len, $TSRMLS_DC) {}
function add_property_resource($arg, $key, $r) {}
function add_property_resource_ex($arg, $key, $key_len, $r, $TSRMLS_DC) {}
function add_property_rt_string($arg, $key, $str, $duplicate) {}
function add_property_rt_string_ex($arg, $key, $key_len, $str, $duplicate, $TSRMLS_DC) {}
function add_property_rt_stringl($arg, $key, $str, $length, $duplicate) {}
function add_property_rt_stringl_ex($arg, $key, $key_len, $str, $length, $duplicate, $TSRMLS_DC) {}
function add_property_string($arg, $key, $str, $duplicate) {}
function add_property_string_ex($arg, $key, $key_len, $str, $duplicate, $TSRMLS_DC) {}
function add_property_stringl($arg, $key, $str, $length, $duplicate) {}
function add_property_stringl_ex($arg, $key, $key_len, $str, $length, $duplicate, $TSRMLS_DC) {}
function add_property_unicode($arg, $key, $str, $duplicate) {}
function add_property_unicode_ex($arg, $key, $key_len, $str, $duplicate, $TSRMLS_DC) {}
function add_property_unicodel($arg, $key, $str, $length, $duplicate) {}
function add_property_unicodel_ex($arg, $key, $key_len, $str, $length, $duplicate, $TSRMLS_DC) {}
function add_property_unset($arg, $key) {}
function add_property_zval($arg, $key, $value) {}
function add_property_zval_ex($arg, $key, $key_len, $value, $TSRMLS_DC) {}
function add_u_assoc_zval($arg, $type, $key, $value) {}
function add_u_assoc_zval_ex($arg, $type, $key, $key_len, $value) {}
function array_init($arg) {}
function call_user_function($function_table, $object_pp, $function_name, $retval_ptr, $param_count, $params[], $TSRMLS_DC) {}
function call_user_function_ex($function_table, $object_pp, $function_name, $retval_ptr_ptr, $param_count, $params[], $no_separation, $symbol_table, $TSRMLS_DC) {}
function compile_file($file_handle, $type, $TSRMLS_DC) {}
function compile_filename($type, $filename, $TSRMLS_DC) {}
function compile_string($source_string, $filename, $TSRMLS_DC) {}
function destroy_op_array($op_array, $TSRMLS_DC) {}
function destroy_zend_class($pce) {}
function destroy_zend_function($function, $TSRMLS_DC) {}
function display_ini_entries($module) {}
function do_bind_class($opline, $class_table, $compile_time, $TSRMLS_DC) {}
function do_bind_function($opline, $function_table, $compile_time) {}
function do_bind_inherited_class($opline, $class_table, $parent_ce, $compile_time, $TSRMLS_DC) {}
function estrndup($s, $length) {}
function estrndup_rel($s, $length) {}
function eustrdup($s) {}
function eustrndup($s, $length) {}
function eustrndup_rel($s, $length) {}
function execute($op_array, $TSRMLS_DC) {}
function execute_internal($execute_data_ptr, $return_value_used, $TSRMLS_DC) {}
function free_estring($str_p) {}
function full_mem_check($silent) {}
function function_add_ref($function, $TSRMLS_DC) {}
function get_active_class_name($space, $TSRMLS_DC) {}
function get_active_function_name($TSRMLS_D) {}
function get_binary_op($opcode) {}
function get_unary_op($opcode) {}
function get_zend_version($void) {}
function highlight_file($filename, $syntax_highlighter_ini, $TSRMLS_DC) {}
function highlight_string($str, $syntax_highlighter_ini, $str_name, $TSRMLS_DC) {}
function init_op_array($op_array, $type, $initial_ops_size, $TSRMLS_DC) {}
function lex_scan($zendlval, $TSRMLS_DC) {}
function mem_block_check($ptr, $silent) {}
function object_and_properties_init($arg, $ce, $properties) {}
function object_init($arg) {}
function object_init_ex($arg, $ce) {}
function open_file_for_scanning($file_handle, $TSRMLS_DC) {}
function register_list_destructors($ld, $pld) {}
function shutdown_memory_manager($silent, $full_shutdown, $TSRMLS_DC) {}
function start_memory_manager($TSRMLS_D) {}
function zend_alter_ini_entry($name, $name_length, $new_value, $new_value_length, $modify_type, $stage) {}
function zend_auto_global_disable_jit($varname, $varname_length, $TSRMLS_DC) {}
function zend_bailout() {}
function zend_call_function($fci, $fci_cache, $TSRMLS_DC) {}
function zend_call_method($object_pp, $obj_ce, $fn_proxy, $function_name, $function_name_len, $retval_ptr_ptr, $param_count, $arg1, $arg2, $TSRMLS_DC) {}
function zend_call_method_with_0_params($obj, $obj_ce, $fn_proxy, $function_name, $retval) {}
function zend_call_method_with_1_params($obj, $obj_ce, $fn_proxy, $function_name, $retval, $arg1) {}
function zend_call_method_with_2_params($obj, $obj_ce, $fn_proxy, $function_name, $retval, $arg1, $arg2) {}
function zend_case_fold_string($dest, $dest_len, $src, $src_len, $options, $status) {}
function zend_check_magic_method_implementation($ce, $fptr, $error_type, $TSRMLS_DC) {}
function zend_check_private($fbc, $ce, $function_name_strval, $function_name_strlen, $TSRMLS_DC) {}
function zend_check_property_access($zobj, $utype, $prop_info_name, $TSRMLS_DC) {}
function zend_check_protected($ce, $scope) {}
function zend_class_implements($class_entry, $TSRMLS_DC, $num_interfaces) {}
function zend_cleanup_class_data($pce, $TSRMLS_DC) {}
function zend_cleanup_function_data($function, $TSRMLS_DC) {}
function zend_clear_exception($TSRMLS_D) {}
function zend_cmp_unicode_and_literal($ustr, $ulen, $str, $slen) {}
function zend_cmp_unicode_and_string($ustr, $str, $len) {}
function zend_convert_encodings($target_conv, $source_conv, $target, $target_len, $source, $source_len, $status) {}
function zend_convert_from_unicode($conv, $target, $target_len, $source, $source_len, $status) {}
function zend_convert_scanner_output($target, $target_len, $source, $source_len, $status, $TSRMLS_DC) {}
function zend_convert_to_unicode($conv, $target, $target_len, $source, $source_len, $status) {}
function zend_copy_ini_directives($TSRMLS_D) {}
function zend_copy_parameters_array($param_count, $argument_array, $TSRMLS_DC) {}
function zend_declare_class_constant($ce, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_declare_class_constant_bool($ce, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_declare_class_constant_double($ce, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_declare_class_constant_long($ce, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_declare_class_constant_string($ce, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_declare_class_constant_stringl($ce, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_declare_property($ce, $name, $name_length, $property, $access_type, $TSRMLS_DC) {}
function zend_declare_property_bool($ce, $name, $name_length, $value, $access_type, $TSRMLS_DC) {}
function zend_declare_property_double($ce, $name, $name_length, $value, $access_type, $TSRMLS_DC) {}
function zend_declare_property_ex($ce, $name, $name_length, $property, $access_type, $doc_comment, $doc_comment_len, $TSRMLS_DC) {}
function zend_declare_property_long($ce, $name, $name_length, $value, $access_type, $TSRMLS_DC) {}
function zend_declare_property_null($ce, $name, $name_length, $access_type, $TSRMLS_DC) {}
function zend_declare_property_string($ce, $name, $name_length, $value, $access_type, $TSRMLS_DC) {}
function zend_declare_property_stringl($ce, $name, $name_length, $value, $value_len, $access_type, $TSRMLS_DC) {}
function zend_delete_global_variable($name, $name_len, $TSRMLS_DC) {}
function zend_destroy_file_handle($file_handle, $TSRMLS_DC) {}
function zend_disable_class($class_name, $class_name_length, $TSRMLS_DC) {}
function zend_disable_function($function_name, $function_name_length, $TSRMLS_DC) {}
function zend_do_fcall($ZEND_OPCODE_HANDLER_ARGS) {}
function zend_do_implement_interface($ce, $iface, $TSRMLS_DC) {}
function zend_do_inherit_interfaces($ce, $iface, $TSRMLS_DC) {}
function zend_do_inheritance($ce, $parent_ce, $TSRMLS_DC) {}
function zend_error($type, $format) {}
function zend_eval_string($str, $retval_ptr, $string_name, $TSRMLS_DC) {}
function zend_eval_string_ex($str, $retval_ptr, $string_name, $handle_exceptions, $TSRMLS_DC) {}
function zend_exception_error($exception, $TSRMLS_DC) {}
function zend_exception_get_default($TSRMLS_D) {}
function zend_execute_scripts($type, $TSRMLS_DC, $retval, $file_count) {}
function zend_fetch_class($class_name, $class_name_len, $fetch_type, $TSRMLS_DC) {}
function zend_fetch_debug_backtrace($return_value, $skip_last, $provide_object, $TSRMLS_DC) {}
function zend_fetch_list_dtor_id($type_name) {}
function zend_fetch_resource($passed_id, $TSRMLS_DC, $default_id, $resource_type_name, $found_resource_type, $num_resource_types) {}
function zend_file_handle_dtor($fh) {}
function zend_function_dtor($function) {}
function zend_get_class_entry($zobject, $TSRMLS_DC) {}
function zend_get_compiled_filename($TSRMLS_D) {}
function zend_get_compiled_lineno($TSRMLS_D) {}
function zend_get_compiled_script_encoding($TSRMLS_D) {}
function zend_get_compiled_variable_name($op_array, $var, $name_len) {}
function zend_get_compiled_variable_value($execute_data_ptr, $var) {}
function zend_get_configuration_directive($name, $name_length, $contents) {}
function zend_get_constant($name, $name_len, $result, $TSRMLS_DC) {}
function zend_get_error_exception($TSRMLS_D) {}
function zend_get_executed_filename($TSRMLS_D) {}
function zend_get_executed_lineno($TSRMLS_D) {}
function zend_get_hash_value($arKey, $nKeyLength) {}
function zend_get_module_started($module_name) {}
function zend_get_module_version($module_name) {}
function zend_get_object_classname($object, $class_name, $class_name_len, $TSRMLS_DC) {}
function zend_get_parameters($ht, $param_count) {}
function zend_get_parameters_array($ht, $param_count, $argument_array) {}
function zend_get_parameters_array_ex($param_count, $argument_array) {}
function zend_get_parameters_ex($param_count) {}
function zend_get_scanned_file_offset($TSRMLS_D) {}
function zend_get_std_object_handlers() {}
function zend_get_unified_string_type($num_args, $TSRMLS_DC) {}
function zend_get_user_opcode_handler($opcode) {}
function zend_get_zval_ptr($node, $Ts, $should_free, $type, $TSRMLS_DC) {}
function zend_get_zval_ptr_ptr($node, $Ts, $should_free, $type, $TSRMLS_DC) {}
function zend_hash_add($ht, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_hash_add_empty_element($ht, $arKey, $nKeyLength) {}
function zend_hash_apply($ht, $apply_func, $TSRMLS_DC) {}
function zend_hash_apply_with_argument($ht, $apply_func, $TSRMLS_DC) {}
function zend_hash_apply_with_arguments($ht, $apply_func, $int) {}
function zend_hash_clean($ht) {}
function zend_hash_compare($ht1, $ht2, $compar, $ordered, $TSRMLS_DC) {}
function zend_hash_copy($target, $source, $pCopyConstructor, $tmp, $size) {}
function zend_hash_del($ht, $arKey, $nKeyLength) {}
function zend_hash_del_key_or_index($ht, $arKey, $nKeyLength, $h, $flag) {}
function zend_hash_destroy($ht) {}
function zend_hash_exists($ht, $arKey, $nKeyLength) {}
function zend_hash_find($ht, $arKey, $nKeyLength, $pData) {}
function zend_hash_func($arKey, $nKeyLength) {}
function zend_hash_get_current_data($ht, $pData) {}
function zend_hash_get_current_data_ex($ht, $pData, $pos) {}
function zend_hash_get_current_key($ht, $str_index, $num_index, $duplicate) {}
function zend_hash_get_current_key_ex($ht, $str_index, $str_length, $num_index, $duplicate, $pos) {}
function zend_hash_get_current_key_type($ht) {}
function zend_hash_get_current_key_type_ex($ht, $pos) {}
function zend_hash_graceful_destroy($ht) {}
function zend_is_true($op) {}
function zend_hash_graceful_reverse_destroy($ht) {}
function zend_hash_index_del($ht, $h) {}
function zend_hash_index_exists($ht, $h) {}
function zend_hash_index_find($ht, $h, $pData) {}
function zend_hash_index_update($ht, $h, $pData, $nDataSize, $pDest) {}
function zend_hash_init($ht, $nSize, $pHashFunction, $pDestructor, $persistent) {}
function zend_hash_init_ex($ht, $nSize, $pHashFunction, $pDestructor, $persistent, $bApplyProtection) {}
function zend_hash_internal_pointer_end($ht) {}
function zend_hash_internal_pointer_end_ex($ht, $pos) {}
function zend_hash_internal_pointer_reset($ht) {}
function zend_hash_internal_pointer_reset_ex($ht, $pos) {}
function zend_hash_merge($target, $source, $pCopyConstructor, $tmp, $size, $overwrite) {}
function zend_hash_merge_ex($target, $source, $pCopyConstructor, $size, $pMergeSource, $pParam) {}
function zend_hash_minmax($ht, $compar, $flag, $pData, $TSRMLS_DC) {}
function zend_hash_move_backwards($ht) {}
function zend_hash_move_backwards_ex($ht, $pos) {}
function zend_hash_move_forward($ht) {}
function zend_hash_move_forward_ex($ht, $pos) {}
function zend_hash_next_free_element($ht) {}
function zend_hash_next_index_insert($ht, $pData, $nDataSize, $pDest) {}
function zend_hash_num_elements($ht) {}
function zend_hash_quick_add($ht, $arKey, $nKeyLength, $h, $pData, $nDataSize, $pDest) {}
function zend_hash_quick_exists($ht, $arKey, $nKeyLength, $h) {}
function zend_hash_quick_find($ht, $arKey, $nKeyLength, $h, $pData) {}
function zend_hash_quick_update($ht, $arKey, $nKeyLength, $h, $pData, $nDataSize, $pDest) {}
function zend_hash_rehash($ht) {}
function zend_hash_reverse_apply($ht, $apply_func, $TSRMLS_DC) {}
function zend_hash_sort($ht, $sort_func, $compare_func, $renumber, $TSRMLS_DC) {}
function zend_hash_update($ht, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_hash_update_current_key($ht, $key_type, $str_index, $str_length, $num_index) {}
function zend_hash_update_current_key_ex($ht, $key_type, $str_index, $str_length, $num_index, $pos) {}
function zend_highlight($syntax_highlighter_ini, $TSRMLS_DC) {}
function zend_html_putc($c) {}
function zend_html_puts($s, $len, $TSRMLS_DC) {}
function zend_ini_deactivate($TSRMLS_D) {}
function zend_ini_double($name, $name_length, $orig) {}
function zend_ini_global_shutdown($TSRMLS_D) {}
function zend_ini_long($name, $name_length, $orig) {}
function zend_ini_refresh_caches($stage, $TSRMLS_DC) {}
function zend_ini_register_displayer($name, $name_length, $(*displayer) {}
function zend_ini_shutdown($TSRMLS_D) {}
function zend_ini_sort_entries($TSRMLS_D) {}
function zend_ini_startup($TSRMLS_D) {}
function zend_ini_string($name, $name_length, $orig) {}
function zend_initialize_class_data($ce, $nullify_handlers, $TSRMLS_DC) {}
function zend_is_auto_global($name, $name_len, $TSRMLS_DC) {}
function zend_is_callable($callable, $check_flags, $callable_name) {}
function zend_is_callable_ex($callable, $check_flags, $callable_name, $ce_ptr, $fptr_ptr, $zobj_ptr_ptr, $TSRMLS_DC) {}
function zend_is_compiling($TSRMLS_D) {}
function zend_is_executing($TSRMLS_D) {}
function zend_is_valid_identifier($ident, $ident_len) {}
function zend_list_addref($id) {}
function zend_list_delete($id) {}
function zend_list_find($id, $type) {}
function zend_list_insert($ptr, $type) {}
function zend_lookup_class($name, $name_length, $ce, $TSRMLS_DC) {}
function zend_make_callable($callable, $callable_name, $TSRMLS_DC) {}
function zend_make_compiled_string_description($name, $TSRMLS_DC) {}
function zend_make_printable_zval($expr, $expr_copy, $use_copy) {}
function zend_make_string_zval($expr, $expr_copy, $use_copy) {}
function zend_make_unicode_zval($expr, $expr_copy, $use_copy) {}
function zend_mangle_property_name($dest, $dest_length, $src1, $src1_length, $src2, $src2_length, $internal) {}
function zend_merge_properties($obj, $properties, $destroy_ht, $TSRMLS_DC) {}
function zend_message_dispatcher($message, $data) {}
function zend_normalize_identifier($dest, $dest_len, $ident, $ident_len, $fold_case) {}
function zend_object_create_proxy($object, $member, $TSRMLS_DC) {}
function zend_object_store_ctor_failed($zobject, $TSRMLS_DC) {}
function zend_object_store_get_object($object, $TSRMLS_DC) {}
function zend_object_store_set_object($zobject, $object, $TSRMLS_DC) {}
function zend_objects_clone_members($new_object, $new_obj_val, $old_object, $handle, $TSRMLS_DC) {}
function zend_objects_clone_obj($object, $TSRMLS_DC) {}
function zend_objects_destroy_object($object, $handle, $TSRMLS_DC) {}
function zend_objects_free_object_storage($object, $TSRMLS_DC) {}
function zend_objects_get_address($object, $TSRMLS_DC) {}
function zend_objects_new($object, $class_type, $TSRMLS_DC) {}
function zend_objects_store_add_ref($object, $TSRMLS_DC) {}
function zend_objects_store_call_destructors($objects, $TSRMLS_DC) {}
function zend_objects_store_clone_obj($object, $TSRMLS_DC) {}
function zend_objects_store_del_ref($object, $TSRMLS_DC) {}
function zend_objects_store_destroy($objects) {}
function zend_objects_store_free_object_storage($objects, $TSRMLS_DC) {}
function zend_objects_store_init($objects, $init_size) {}
function zend_objects_store_mark_destructed($objects, $TSRMLS_DC) {}
function zend_objects_store_put($object, $dtor, $storage, $clone, $TSRMLS_DC) {}
function zend_output_debug_string($trigger_break, $format) {}
function zend_parse_ini_file($fh, $unbuffered_errors, $ini_parser_cb, $arg) {}
function zend_parse_method_parameters($num_args, $TSRMLS_DC, $this_ptr, $type_spec) {}
function zend_parse_method_parameters_ex($flags, $num_args, $TSRMLS_DC, $this_ptr, $type_spec) {}
function zend_parse_parameters($num_args, $TSRMLS_DC, $type_spec) {}
function zend_parse_parameters_ex($flags, $num_args, $TSRMLS_DC, $type_spec) {}
function zend_prepare_scanner_converters($onetime_encoding, $run_time, $TSRMLS_DC) {}
function zend_print_flat_zval_r($expr, $TSRMLS_DC) {}
function zend_print_variable($var) {}
function zend_print_zval($expr, $indent) {}
function zend_print_zval_ex($write_func, $expr, $indent) {}
function zend_print_zval_r($expr, $indent, $TSRMLS_DC) {}
function zend_print_zval_r_ex($write_func, $expr, $indent, $TSRMLS_DC) {}
function zend_qsort($base, $nmemb, $siz, $compare, $TSRMLS_DC) {}
function zend_read_property($scope, $object, $name, $name_length, $silent, $TSRMLS_DC) {}
function zend_read_static_property($scope, $name, $name_length, $silent, $TSRMLS_DC) {}
function zend_register_auto_global($name, $name_len, $auto_global_callback, $TSRMLS_DC) {}
function zend_register_constant($c, $TSRMLS_DC) {}
function zend_register_default_classes($TSRMLS_D) {}
function zend_register_double_constant($name, $name_len, $dval, $flags, $module_number, $TSRMLS_DC) {}
function zend_register_functions($scope, $functions, $function_table, $type, $TSRMLS_DC) {}
function zend_register_ini_entries($ini_entry, $module_number, $TSRMLS_DC) {}
function zend_register_interfaces($TSRMLS_D) {}
function zend_register_internal_class($class_entry, $TSRMLS_DC) {}
function zend_register_internal_class_ex($class_entry, $parent_ce, $parent_name, $TSRMLS_DC) {}
function zend_register_internal_interface($orig_class_entry, $TSRMLS_DC) {}
function zend_register_internal_module($module_entry, $TSRMLS_DC) {}
function zend_register_list_destructors($), $), $module_number) {}
function zend_register_module($module_entry) {}
function zend_register_list_destructors_ex($ld, $pld, $type_name, $module_number) {}
function zend_register_long_constant($name, $name_len, $lval, $flags, $module_number, $TSRMLS_DC) {}
function zend_register_module_ex($module, $TSRMLS_DC) {}
function zend_register_resource($rsrc_result, $rsrc_pointer, $rsrc_type) {}
function zend_register_string_constant($name, $name_len, $strval, $flags, $module_number, $TSRMLS_DC) {}
function zend_register_stringl_constant($name, $name_len, $strval, $strlen, $flags, $module_number, $TSRMLS_DC) {}
function zend_reset_all_cv($symbol_table, $TSRMLS_DC) {}
function zend_reset_locale_deps($TSRMLS_D) {}
function zend_restore_compiled_filename($original_compiled_filename, $TSRMLS_DC) {}
function zend_restore_compiled_script_encoding($original_script_enc, $TSRMLS_DC) {}
function zend_restore_ini_entry($name, $name_length, $stage) {}
function zend_rsrc_list_get_rsrc_type($resource, $TSRMLS_DC) {}
function zend_set_compiled_filename($new_compiled_filename, $TSRMLS_DC) {}
function zend_set_compiled_script_encoding($new_script_enc, $TSRMLS_DC) {}
function zend_set_memory_limit($memory_limit) {}
function zend_set_timeout($seconds) {}
function zend_set_user_opcode_handler($opcode, $handler) {}
function zend_startup_module($module_entry) {}
function zend_startup_module_ex($module, $TSRMLS_DC) {}
function zend_startup_modules($TSRMLS_D) {}
function zend_std_call_user_call($INTERNAL_FUNCTION_PARAMETERS) {}
function zend_std_cast_object_tostring($readobj, $writeobj, $type, $TSRMLS_DC) {}
function zend_std_get_static_property($ce, $type, $property_name, $property_name_len, $silent, $TSRMLS_DC) {}
function zend_std_unset_static_property($ce, $type, $property_name, $property_name_len, $TSRMLS_DC) {}
function zend_stream_close($handle) {}
function zend_stream_ferror($file_handle, $TSRMLS_DC) {}
function zend_stream_fixup($file_handle, $TSRMLS_DC) {}
function zend_stream_ftell($file_handle, $TSRMLS_DC) {}
function zend_stream_getc($file_handle, $TSRMLS_DC) {}
function zend_stream_open($filename, $handle, $TSRMLS_DC) {}
function zend_stream_read($file_handle, $buf, $len, $TSRMLS_DC) {}
function zend_strip($TSRMLS_D) {}
function zend_strndup($s, $length) {}
function zend_strtod($s00, $se) {}
function zend_symtable_del($ht, $arKey, $nKeyLength) {}
function zend_symtable_exists($ht, $arKey, $nKeyLength) {}
function zend_symtable_find($ht, $arKey, $nKeyLength, $pData) {}
function zend_symtable_update($ht, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_symtable_update_current_key($ht, $arKey, $nKeyLength) {}
function zend_throw_exception_object($exception, $TSRMLS_DC) {}
function zend_timeout($dummy) {}
function zend_u_declare_property($ce, $type, $name, $name_length, $property, $access_type, $TSRMLS_DC) {}
function zend_u_declare_property_ex($ce, $type, $name, $name_length, $property, $access_type, $doc_comment, $doc_comment_len, $TSRMLS_DC) {}
function zend_u_delete_global_variable($type, $name, $name_len, $TSRMLS_DC) {}
function zend_u_eval_string($type, $str, $retval_ptr, $string_name, $TSRMLS_DC) {}
function zend_u_eval_string_ex($type, $str, $retval_ptr, $string_name, $handle_exceptions, $TSRMLS_DC) {}
function zend_u_fetch_class($type, $class_name, $class_name_len, $fetch_type, $TSRMLS_DC) {}
function zend_u_get_constant($type, $name, $name_len, $result, $TSRMLS_DC) {}
function zend_u_get_hash_value($type, $arKey, $nKeyLength) {}
function zend_u_hash_add($ht, $type, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_u_hash_add_empty_element($ht, $type, $arKey, $nKeyLength) {}
function zend_u_hash_del($ht, $type, $arKey, $nKeyLength) {}
function zend_u_hash_del_key_or_index($ht, $type, $arKey, $nKeyLength, $h, $flag) {}
function zend_u_hash_exists($ht, $type, $arKey, $nKeyLength) {}
function zend_u_hash_find($ht, $type, $arKey, $nKeyLength, $pData) {}
function zend_u_hash_func($type, $arKey, $nKeyLength) {}
function zend_u_hash_init($ht, $nSize, $pHashFunction, $pDestructor, $persistent, $unicode) {}
function zend_u_hash_init_ex($ht, $nSize, $pHashFunction, $pDestructor, $persistent, $unicode, $bApplyProtection) {}
function zend_u_hash_quick_add($ht, $type, $arKey, $nKeyLength, $h, $pData, $nDataSize, $pDest) {}
function zend_u_hash_quick_exists($ht, $type, $arKey, $nKeyLength, $h) {}
function zend_u_hash_quick_find($ht, $type, $arKey, $nKeyLength, $h, $pData) {}
function zend_u_hash_quick_update($ht, $type, $arKey, $nKeyLength, $h, $pData, $nDataSize, $pDest) {}
function zend_u_hash_update($ht, $type, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_u_is_auto_global($type, $name, $name_len, $TSRMLS_DC) {}
function zend_u_lookup_class($type, $name, $name_length, $ce, $TSRMLS_DC) {}
function zend_u_lookup_class_ex($type, $name, $name_length, $use_autoload, $ce, $TSRMLS_DC) {}
function zend_u_mangle_property_name($dest, $dest_length, $type, $src1, $src1_length, $src2, $src2_length, $internal) {}
function zend_u_register_constant($type, $c, $TSRMLS_DC) {}
function zend_u_symtable_del($ht, $type, $arKey, $nKeyLength) {}
function zend_u_symtable_exists($ht, $type, $arKey, $nKeyLength) {}
function zend_u_symtable_find($ht, $type, $arKey, $nKeyLength, $pData) {}
function zend_u_symtable_update($ht, $type, $arKey, $nKeyLength, $pData, $nDataSize, $pDest) {}
function zend_u_symtable_update_current_key($ht, $type, $arKey, $nKeyLength) {}
function zend_u_unmangle_property_name($type, $mangled_property, $prop_name, $class_name) {}
function zend_unmangle_property_name($mangled_property, $prop_name, $class_name) {}
function zend_unregister_functions($functions, $count, $function_table, $TSRMLS_DC) {}
function zend_unregister_ini_entries($module_number, $TSRMLS_DC) {}
function zend_unset_timeout($TSRMLS_D) {}
function zend_update_class_constants($class_type, $TSRMLS_DC) {}
function zend_update_property($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_ascii_string($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_ascii_stringl($scope, $object, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_property_bool($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_double($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_long($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_null($scope, $object, $name, $name_length, $TSRMLS_DC) {}
function zend_update_property_rt_string($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_rt_stringl($scope, $object, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_property_string($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_stringl($scope, $object, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_property_unicode($scope, $object, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_property_unicodel($scope, $object, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_static_property($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_ascii_string($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_ascii_stringl($scope, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_static_property_bool($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_double($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_long($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_null($scope, $name, $name_length, $TSRMLS_DC) {}
function zend_update_static_property_rt_string($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_rt_stringl($scope, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_static_property_string($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_stringl($scope, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_update_static_property_unicode($scope, $name, $name_length, $value, $TSRMLS_DC) {}
function zend_update_static_property_unicodel($scope, $name, $name_length, $value, $value_length, $TSRMLS_DC) {}
function zend_ustrndup($s, $length) {}
function zend_wrong_param_count($TSRMLS_D) {}
function zend_zval_type_name($arg) {}
function zval_add_ref($p) {}
function zval_internal_dtor($zvalue) {}
function zval_internal_ptr_dtor($zvalue) {}
function zval_ptr_dtor($zval_ptr) {}
function zval_string_to_unicode($string, $TSRMLS_DC) {}
function zval_string_to_unicode_ex($string, $conv) {}
function zval_unicode_to_string($string, $conv, $TSRMLS_DC) {}
function zval_update_constant($pp, $arg, $TSRMLS_DC) {}
function DISPLAY_INI_ENTRIES() {}
function INI_BOOL($name) ((zend_bool) {}
function INI_FLT($name) {}
function INI_INT($name) {}
function INI_ORIG_BOOL($name) ((zend_bool) {}
function INI_ORIG_FLT($name) {}
function INI_ORIG_INT($name) {}
function INI_ORIG_STR($name) {}
function INI_STR($name) {}
function REGISTER_DOUBLE_CONSTANT($name, $dval, $flags) {}
function REGISTER_INI_BOOLEAN($name) {}
function REGISTER_INI_DISPLAYER($name, $displayer) {}
function REGISTER_INI_ENTRIES() {}
function REGISTER_LONG_CONSTANT($name, $lval, $flags) {}
function REGISTER_MAIN_DOUBLE_CONSTANT($name, $dval, $flags) {}
function REGISTER_MAIN_LONG_CONSTANT($name, $lval, $flags) {}
function REGISTER_MAIN_STRING_CONSTANT($name, $str, $flags) {}
function REGISTER_MAIN_STRINGL_CONSTANT($name, $str, $len, $flags) {}
function REGISTER_STRING_CONSTANT($name, $str, $flags) {}
function REGISTER_STRINGL_CONSTANT($name, $str, $len, $flags) {}
function RETURN_ASCII_STRING($t, $duplicate) {}
function RETURN_ASCII_STRINGL($t, $l, $duplicate) {}
function RETURN_BINARY($s, $duplicate) {}
function RETURN_BINARYL($s, $l, $duplicate) {}
function RETURN_BOOL($b) {}
function RETURN_DOUBLE($d) {}
function RETURN_EMPTY_BINARY() {}
function RETURN_EMPTY_STRING() {}
function RETURN_EMPTY_UNICODE() {}
function RETURN_LONG($l) {}
function RETURN_NULL() {}
function RETURN_RESOURCE($r) {}
function RETURN_RT_STRING($t, $duplicate) {}
function RETURN_RT_STRINGL($t, $l, $duplicate) {}
function RETURN_STRING($s, $duplicate) {}
function RETURN_STRINGL($s, $l, $duplicate) {}
function RETURN_TEXT($t, $duplicate) {}
function RETURN_TEXTL($t, $l, $duplicate) {}
function RETURN_U_STRING($conv, $t, $duplicate) {}
function RETURN_U_STRINGL($conv, $t, $l, $duplicate) {}
function RETURN_UNICODE($u, $duplicate) {}
function RETURN_UNICODEL($u, $l, $duplicate) {}
function RETURN_ZVAL($zv, $copy, $dtor) {}
function UNREGISTER_INI_ENTRIES() {}
function Z_ARRVAL($zval) {}
function Z_ARRVAL_P($zval_p) {}
function Z_ARRVAL_PP($zval_pp) {}
function Z_BINLEN($zval) {}
function Z_BINLEN_P($zval) {}
function Z_BINLEN_PP($zval) {}
function Z_BINVAL($zval) {}
function Z_BINVAL_P($zval) {}
function Z_BINVAL_PP($zval) {}
function Z_BVAL($zv) {}
function Z_BVAL_P($zval_p) {}
function Z_BVAL_PP($zval_pp) {}
function Z_DBG($expr) {}
function Z_DVAL($zval) {}
function Z_DVAL_P($zval_p) {}
function Z_DVAL_PP($zval_pp) {}
function Z_LVAL($zval) {}
function Z_LVAL_P($zval_p) {}
function Z_LVAL_PP($zval_pp) {}
function Z_OBJ_CLASS_NAME_P($zval) {}
function Z_OBJ_HANDLE($zval) {}
function Z_OBJ_HANDLE_P($zval_p) {}
function Z_OBJ_HANDLE_PP($zval_p) {}
function Z_OBJ_HANDLER($zval, $hf) {}
function Z_OBJ_HANDLER_P($zval_p, $h) {}
function Z_OBJ_HANDLER_PP($zval_p, $h) {}
function Z_OBJ_HT($zval) {}
function Z_OBJ_HT_P($zval_p) {}
function Z_OBJ_HT_PP($zval_p) {}
function Z_OBJCE($zval) {}
function Z_OBJCE_P($zval_p) {}
function Z_OBJCE_PP($zval_pp) {}
function Z_OBJPROP($zval) {}
function Z_OBJPROP_P($zval_p) {}
function Z_OBJPROP_PP($zval_pp) {}
function Z_OBJVAL($zval) {}
function Z_OBJVAL_P($zval_p) {}
function Z_OBJVAL_PP($zval_pp) {}
function Z_RESVAL($zval) {}
function Z_RESVAL_P($zval_p) {}
function Z_RESVAL_PP($zval_pp) {}
function Z_STRLEN($zval) {}
function Z_STRLEN_P($zval_p) {}
function Z_STRLEN_PP($zval_pp) {}
function Z_STRVAL($zval) {}
function Z_STRVAL_P($zval_p) {}
function Z_STRVAL_PP($zval_pp) {}
function Z_TYPE($zv) {}
function Z_TYPE_P($zval_p) {}
function Z_TYPE_PP($zval_pp) {}
function Z_UNILEN($zval) {}
function Z_UNILEN_P($zval_p) {}
function Z_UNILEN_PP($zval_pp) {}
function Z_UNIVAL($zval) {}
function Z_UNIVAL_P($zval_p) {}
function Z_UNIVAL_PP($zval_pp) {}
function Z_USTRCPLEN($zval) {}
function Z_USTRCPLEN_P($zval_p) {}
function Z_USTRCPLEN_PP($zval_pp) {}
function Z_USTRLEN($zval) {}
function Z_USTRLEN_P($zval_p) {}
function Z_USTRLEN_PP($zval_pp) {}
function Z_USTRVAL($zval) {}
function Z_USTRVAL_P($zval_p) {}
function Z_USTRVAL_PP($zval_pp) {}
function ZEND_ABSTRACT_ME($classname, $name, $arg_info) {}
function ZEND_ARG_ARRAY_INFO($pass_by_ref, $name, $allow_null) {}
function ZEND_ARG_INFO($pass_by_ref, $name) {}
function ZEND_ARG_OBJ_INFO($pass_by_ref, $name, $classname, $allow_null) {}
function ZEND_ARG_PASS_INFO($pass_by_ref) {}
function ZEND_BEGIN_ARG_INFO($name, $pass_rest_by_reference) {}
function ZEND_BEGIN_ARG_INFO_EX($name, $pass_rest_by_reference, $return_reference, $required_num_args) {}
function ZEND_BEGIN_MODULE_GLOBALS($module_name) {}
function ZEND_COLL_RESULT($n) {}
function ZEND_DECLARE_MODULE_GLOBALS($module_name) {}
function ZEND_DEFINE_PROPERTY($class_ptr, $name, $value, $mask) {}
function ZEND_END_ARG_INFO() {}
function ZEND_END_MODULE_GLOBALS($module_name) {}
function ZEND_EXTERN_MODULE_GLOBALS($module_name) {}
function ZEND_FALIAS($name, $alias, $arg_info) {}
function ZEND_FE($name, $arg_info) {}
function ZEND_FENTRY($zend_name, $name, $arg_info, $flags) {}
function ZEND_FETCH_RESOURCE($rsrc, $rsrc_type, $passed_id, $default_id, $resource_type_name, $resource_type) {}
function ZEND_FETCH_RESOURCE2($rsrc, $rsrc_type, $passed_id, $default_id, $resource_type_name, $resource_type1, $resource_type2) {}
function ZEND_FN($name) {}
function ZEND_FN_SCOPE_NAME($function) {}
function ZEND_FUNCTION($name) {}
function ZEND_GET_MODULE($name) {}
function ZEND_GET_RESOURCE_TYPE_ID($le_id, $le_type_name) {}
function ZEND_INI_BEGIN() {}
function ZEND_INI_DISP($name) {}
function ZEND_INI_END() {}
function ZEND_INI_ENTRY($name, $default_value, $modifiable, $on_modify) {}
function ZEND_INI_ENTRY1($name, $default_value, $modifiable, $on_modify, $arg1) {}
function ZEND_INI_ENTRY1_EX($name, $default_value, $modifiable, $on_modify, $arg1, $displayer) {}
function ZEND_INI_ENTRY2($name, $default_value, $modifiable, $on_modify, $arg1, $arg2) {}
function ZEND_INI_ENTRY2_EX($name, $default_value, $modifiable, $on_modify, $arg1, $arg2, $displayer) {}
function ZEND_INI_ENTRY3($name, $default_value, $modifiable, $on_modify, $arg1, $arg2, $arg3) {}
function ZEND_INI_ENTRY3_EX($name, $default_value, $modifiable, $on_modify, $arg1, $arg2, $arg3, $displayer) {}
function ZEND_INI_ENTRY_EX($name, $default_value, $modifiable, $on_modify, $displayer) {}
function ZEND_INI_MH($name) {}
function ZEND_INIT_MODULE_GLOBALS($module_name, $globals_ctor, $globals_dtor) {}
function ZEND_INIT_SYMTABLE($ht) {}
function ZEND_INIT_SYMTABLE_EX($ht, $n, $persistent) {}
function ZEND_LOG_XOR($a, $b) {}
function ZEND_MALIAS($classname, $name, $alias, $arg_info, $flags) {}
function ZEND_ME($classname, $name, $arg_info, $flags) {}
function ZEND_ME_MAPPING($name, $func_name, $arg_types) {}
function ZEND_METHOD($classname, $name) {}
function ZEND_MOD_CONFLICTS($name) {}
function ZEND_MOD_CONFLICTS_EX($name, $rel, $ver) {}
function ZEND_MOD_OPTIONAL($name) {}
function ZEND_MOD_OPTIONAL_EX($name, $rel, $ver) {}
function ZEND_MOD_REQUIRED($ext_name) {}
function ZEND_MOD_REQUIRED_EX($name, $rel, $ver) {}
function ZEND_MODULE_ACTIVATE_D($module) {}
function ZEND_MODULE_ACTIVATE_N($module) {}
function ZEND_MODULE_DEACTIVATE_D($module) {}
function ZEND_MODULE_DEACTIVATE_N($module) {}
function ZEND_MODULE_INFO_D($module) {}
function ZEND_MODULE_INFO_N($module) {}
function ZEND_MODULE_POST_ZEND_DEACTIVATE_D($module) {}
function ZEND_MODULE_POST_ZEND_DEACTIVATE_N($module) {}
function ZEND_MODULE_SHUTDOWN_D($module) {}
function ZEND_MODULE_SHUTDOWN_N($module) {}
function ZEND_MODULE_STARTUP_D($module) {}
function ZEND_MODULE_STARTUP_N($module) {}
function ZEND_NAMED_FE($zend_name, $name, $arg_info) {}
function ZEND_NAMED_FUNCTION($name) {}
function ZEND_NORMALIZE_BOOL($n) {}
function ZEND_NUM_ARGS() {}
function ZEND_PUTC($c) {}
function ZEND_PUTS($str) {}
function ZEND_REGISTER_RESOURCE($rsrc_result, $rsrc_pointer, $rsrc_type) {}
function ZEND_RSRC_DTOR_FUNC($name) {}
function ZEND_SET_GLOBAL_VAR($name, $var) {}
function ZEND_SET_GLOBAL_VAR_WITH_LENGTH($name, $name_length, $var, $_refcount, $_is_ref) {}
function ZEND_SET_SYMBOL($symtable, $name, $var) {}
function ZEND_SET_SYMBOL_WITH_LENGTH($symtable, $name, $name_length, $var, $_refcount, $_is_ref) {}
function ZEND_STRL($str) {}
function ZEND_STRS($str) {}
function ZEND_TRUTH($x) {}
function ZEND_U_CONVERTER($c) {}
function ZEND_U_EQUAL($type, $ustr, $ulen, $str, $slen) {}
function ZEND_U_SET_SYMBOL_WITH_LENGTH($symtable, $type, $name, $name_length, $var, $_refcount, $_is_ref) {}
function ZEND_UV($name) {}
function ZEND_VERIFY_RESOURCE($rsrc) {}
function ZEND_WRITE($str, $str_len) {}
function ZEND_WRONG_PARAM_COUNT() {}
function ZEND_WRONG_PARAM_COUNT_WITH_RETVAL($return_value) {}
function apache_child_terminate() {}
function apache_get_modules() {}
function apache_get_version() {}
function apache_getenv($variable, $walk_to_top) {}
function apache_lookup_uri($filename) {}
function apache_note($note_name, $note_value) {}
function apache_request_headers() {}
function apache_reset_timeout() {}
function apache_response_headers() {}
function apache_setenv($variable, $value, $walk_to_top) {}
function ascii2ebcdic($ascii_str) {}
function ebcdic2ascii($ebcdic_str) {}
function getallheaders() {}
function virtual($filename) {}
function apc_add($key, $var, $ttl) {}
function apc_cache_info($cache_type, $limited) {}
function apc_clear_cache($cache_type) {}
function apc_compile_file($filename) {}
function apc_define_constants($key, $constants, $case_sensitive) {}
function apc_delete($key) {}
function apc_fetch($key) {}
function apc_load_constants($key, $case_sensitive) {}
function apc_sma_info($limited) {}
function apc_store($key, $var, $ttl) {}
function apd_breakpoint($debug_level) {}
function apd_callstack() {}
function apd_clunk($warning, $delimiter) {}
function apd_continue($debug_level) {}
function apd_croak($warning, $delimiter) {}
function apd_dump_function_table() {}
function apd_dump_persistent_resources() {}
function apd_dump_regular_resources() {}
function apd_echo($output) {}
function apd_get_active_symbols() {}
function apd_set_pprof_trace($dump_directory, $fragment) {}
function apd_set_session_trace($debug_level, $dump_directory) {}
function apd_set_session($debug_level) {}
function apd_set_socket_session_trace($tcp_server, $socket_type, $port, $debug_level) {}
function override_function($function_name, $function_args, $function_code) {}
function rename_function($original_name, $new_name) {}
function array_change_key_case($input, $case) {}
function array_chunk($input, $size, $preserve_keys) {}
function array_combine($keys, $values) {}
function array_count_values($input) {}
function array_diff_assoc($array1, $array2) {}
function array_diff_key($array1, $array2) {}
function array_diff_uassoc($array1, $array2, $key_compare_func) {}
function array_diff_ukey($array1, $array2, $key_compare_func) {}
function array_diff($array1, $array2) {}
function array_fill_keys($keys, $value) {}
function array_fill($start_index, $num, $value) {}
function array_filter($input, $callback) {}
function array_flip($trans) {}
function array_intersect_assoc($array1, $array2) {}
function array_intersect_key($array1, $array2) {}
function array_intersect_uassoc($array1, $array2, $key_compare_func) {}
function array_intersect_ukey($array1, $array2, $key_compare_func) {}
function array_intersect($array1, $array2) {}
function array_key_exists($key, $search) {}
function array_keys($input, $search_value, $strict) {}
function array_map($callback, $arr1) {}
function array_merge_recursive($array1) {}
function array_merge($array1, $array2) {}
function array_multisort($arr, $arg) {}
function array_pad($input, $pad_size, $pad_value) {}
function array_pop($array) {}
function array_product($array) {}
function array_push($array, $var) {}
function array_rand($input, $num_req) {}
function array_reduce($input, $function, $initial) {}
function array_reverse($array, $preserve_keys) {}
function array_search($needle, $haystack, $strict) {}
function array_shift($array) {}
function array_slice($array, $offset, $length, $preserve_keys) {}
function array_splice($input, $offset, $length, $replacement) {}
function array_sum($array) {}
function array_udiff_assoc($array1, $array2, $data_compare_func) {}
function array_udiff_uassoc($array1, $array2, $data_compare_func, $key_compare_func) {}
function array_udiff($array1, $array2, $data_compare_func) {}
function array_uintersect_assoc($array1, $array2, $data_compare_func) {}
function array_uintersect_uassoc($array1, $array2, $data_compare_func, $key_compare_func) {}
function array_uintersect($array1, $array2, $data_compare_func) {}
function array_unique($array) {}
function array_unshift($array, $var) {}
function array_values($input) {}
function array_walk_recursive($input, $funcname, $userdata) {}
function array_walk($array, $funcname, $userdata) {}
function arsort($array, $sort_flags) {}
function asort($array, $sort_flags) {}
function compact($varname) {}
function count($var, $mode) {}
function current($array) {}
function each($array) {}
function end($array) {}
function extract($var_array, $extract_type, $prefix) {}
function in_array($needle, $haystack, $strict) {}
function key($array) {}
function krsort($array, $sort_flags) {}
function ksort($array, $sort_flags) {}
function natcasesort($array) {}
function natsort($array) {}
function next($array) {}
function prev($array) {}
function range($low, $high, $step) {}
function reset($array) {}
function rsort($array, $sort_flags) {}
function shuffle($array) {}
function sort($array, $sort_flags) {}
function uasort($array, $cmp_function) {}
function uksort($array, $cmp_function) {}
function usort($array, $cmp_function) {}
function bbcode_add_element($bbcode_container, $tag_name, $tag_rules) {}
function bbcode_add_smiley($bbcode_container, $smiley, $replace_by) {}
function bbcode_create($bbcode_initial_tags) {}
function bbcode_destroy($bbcode_container) {}
function bbcode_parse($bbcode_container, $to_parse) {}
function bbcode_set_arg_parser($bbcode_container, $bbcode_arg_parser) {}
function bbcode_set_flags($bbcode_container, $flags, $mode) {}
function bcadd($left_operand, $right_operand, $scale) {}
function bccomp($left_operand, $right_operand, $scale) {}
function bcdiv($left_operand, $right_operand, $scale) {}
function bcmod($left_operand, $modulus) {}
function bcmul($left_operand, $right_operand, $scale) {}
function bcpow($left_operand, $right_operand, $scale) {}
function bcpowmod($left_operand, $right_operand, $modulus, $scale) {}
function bcscale($scale) {}
function bcsqrt($operand, $scale) {}
function bcsub($left_operand, $right_operand, $scale) {}
function bcompiler_load_exe($filename) {}
function bcompiler_load($filename) {}
function bcompiler_parse_class($class, $callback) {}
function bcompiler_read($filehandle) {}
function bcompiler_write_class($filehandle, $className, $extends) {}
function bcompiler_write_constant($filehandle, $constantName) {}
function bcompiler_write_exe_footer($filehandle, $startpos) {}
function bcompiler_write_file($filehandle, $filename) {}
function bcompiler_write_footer($filehandle) {}
function bcompiler_write_function($filehandle, $functionName) {}
function bcompiler_write_functions_from_file($filehandle, $fileName) {}
function bcompiler_write_header($filehandle, $write_ver) {}
function bcompiler_write_included_filename($filehandle, $filename) {}
function bzclose($bz) {}
function bzcompress($source, $blocksize, $workfactor) {}
function bzdecompress($source, $small) {}
function bzerrno($bz) {}
function bzerror($bz) {}
function bzerrstr($bz) {}
function bzflush($bz) {}
function bzopen($filename, $mode) {}
function bzread($bz, $length) {}
function bzwrite($bz, $data, $length) {}
function cal_days_in_month($calendar, $month, $year) {}
function cal_from_jd($jd, $calendar) {}
function cal_info($calendar) {}
function cal_to_jd($calendar, $month, $day, $year) {}
function easter_date($year) {}
function easter_days($year, $method) {}
function frenchtojd($month, $day, $year) {}
function gregoriantojd($month, $day, $year) {}
function jddayofweek($julianday, $mode) {}
function jdmonthname($julianday, $mode) {}
function jdtofrench($juliandaycount) {}
function jdtogregorian($julianday) {}
function jdtojewish($juliandaycount, $hebrew, $fl) {}
function jdtojulian($julianday) {}
function jdtounix($jday) {}
function jewishtojd($month, $day, $year) {}
function juliantojd($month, $day, $year) {}
function unixtojd($timestamp) {}
function classkit_import($filename) {}
function classkit_method_add($classname, $methodname, $args, $code, $flags) {}
function classkit_method_copy($dClass, $dMethod, $sClass, $sMethod) {}
function classkit_method_redefine($classname, $methodname, $args, $code, $flags) {}
function classkit_method_remove($classname, $methodname) {}
function classkit_method_rename($classname, $methodname, $newname) {}
function call_user_method_array($method_name, $obj, $params) {}
function call_user_method($method_name, $obj, $parameter) {}
function class_exists($class_name, $autoload) {}
function get_class_methods($class_name) {}
function get_class_vars($class_name) {}
function get_class($object) {}
function get_declared_classes() {}
function get_declared_interfaces() {}
function get_object_vars($object) {}
function get_parent_class($object) {}
function interface_exists($interface_name, $autoload) {}
function is_a($object, $class_name) {}
function is_subclass_of($object, $class_name) {}
function method_exists($object, $method_name) {}
function property_exists($class, $property) {}
function com_addref() {}
function com_create_guid() {}
function com_event_sink($comobject, $sinkobject, $sinkinterface) {}
function com_get_active_object($progid, $code_page) {}
function com_invoke($com_object, $function_name, $function_parameters) {}
function com_isenum($com_module) {}
function com_load_typelib($typelib_name, $case_insensitive) {}
function com_message_pump($timeoutms) {}
function com_print_typeinfo($comobject, $dispinterface, $wantsink) {}
function com_release() {}
function variant_abs($val) {}
function variant_add($left, $right) {}
function variant_and($left, $right) {}
function variant_cast($variant, $type) {}
function variant_cat($left, $right) {}
function variant_cmp($left, $right, $lcid, $flags) {}
function variant_date_from_timestamp($timestamp) {}
function variant_date_to_timestamp($variant) {}
function variant_div($left, $right) {}
function variant_eqv($left, $right) {}
function variant_fix($variant) {}
function variant_get_type($variant) {}
function variant_idiv($left, $right) {}
function variant_imp($left, $right) {}
function variant_int($variant) {}
function variant_mod($left, $right) {}
function variant_mul($left, $right) {}
function variant_neg($variant) {}
function variant_not($variant) {}
function variant_or($left, $right) {}
function variant_pow($left, $right) {}
function variant_round($variant, $decimals) {}
function variant_set_type($variant, $type) {}
function variant_set($variant, $value) {}
function variant_sub($left, $right) {}
function variant_xor($left, $right) {}
function crack_check($dictionary, $password) {}
function crack_closedict($dictionary) {}
function crack_getlastmessage() {}
function crack_opendict($dictionary) {}
function ctype_alnum($text) {}
function ctype_alpha($text) {}
function ctype_cntrl($text) {}
function ctype_digit($text) {}
function ctype_graph($text) {}
function ctype_lower($text) {}
function ctype_print($text) {}
function ctype_punct($text) {}
function ctype_space($text) {}
function ctype_upper($text) {}
function ctype_xdigit($text) {}
function curl_close($ch) {}
function curl_copy_handle($ch) {}
function curl_errno($ch) {}
function curl_error($ch) {}
function curl_exec($ch) {}
function curl_getinfo($ch, $opt) {}
function curl_init($url) {}
function curl_multi_add_handle($mh, $ch) {}
function curl_multi_close($mh) {}
function curl_multi_exec($mh, $still_running) {}
function curl_multi_getcontent($ch) {}
function curl_multi_info_read($mh, $msgs_in_queue) {}
function curl_multi_init() {}
function curl_multi_remove_handle($mh, $ch) {}
function curl_multi_select($mh, $timeout) {}
function curl_setopt_array($ch, $options) {}
function curl_setopt($ch, $option, $value) {}
function curl_version($age) {}
function cyrus_authenticate($connection, $mechlist, $service, $user, $minssf, $maxssf, $authname, $password) {}
function cyrus_bind($connection, $callbacks) {}
function cyrus_close($connection) {}
function cyrus_connect($host, $port, $flags) {}
function cyrus_query($connection, $query) {}
function cyrus_unbind($connection, $trigger_name) {}
function checkdate($month, $day, $year) {}
function date_add($object, $interval) {}
function date_create($time, $timezone) {}
function date_date_set($object, $year, $month, $day) {}
function date_default_timezone_get() {}
function date_default_timezone_set($timezone_identifier) {}
function date_format($object, $format) {}
function date_isodate_set($object, $year, $week, $day) {}
function date_modify($object, $modify) {}
function date_offset_get($object) {}
function date_parse($date) {}
function date_sub($object, $interval) {}
function date_sun_info($time, $latitude, $longitude) {}
function date_sunrise($timestamp, $format, $latitude, $longitude, $zenith, $gmt_offset) {}
function date_sunset($timestamp, $format, $latitude, $longitude, $zenith, $gmt_offset) {}
function date_time_set($object, $hour, $minute, $second) {}
function date_timezone_get($object) {}
function date_timezone_set($object, $timezone) {}
function date($format, $timestamp) {}
function getdate($timestamp) {}
function gettimeofday($return_float) {}
function gmdate($format, $timestamp) {}
function gmmktime($hour, $minute, $second, $month, $day, $year, $is_dst) {}
function gmstrftime($format, $timestamp) {}
function idate($format, $timestamp) {}
function localtime($timestamp, $is_associative) {}
function microtime($get_as_float) {}
function mktime($hour, $minute, $second, $month, $day, $year, $is_dst) {}
function strftime($format, $timestamp) {}
function strptime($date, $format) {}
function strtotime($time, $now) {}
function time() {}
function timezone_abbreviations_list() {}
function timezone_identifiers_list() {}
function timezone_name_from_abbr($abbr, $gmtOffset, $isdst) {}
function timezone_name_get($object) {}
function timezone_offset_get($object, $datetime) {}
function timezone_open($timezone) {}
function timezone_transitions_get($object) {}
function dba_close($handle) {}
function dba_delete($key, $handle) {}
function dba_exists($key, $handle) {}
function dba_fetch($key, $handle) {}
function dba_firstkey($handle) {}
function dba_handlers($full_info) {}
function dba_insert($key, $value, $handle) {}
function dba_key_split($key) {}
function dba_list() {}
function dba_nextkey($handle) {}
function dba_open($path, $mode, $handler) {}
function dba_optimize($handle) {}
function dba_popen($path, $mode, $handler) {}
function dba_replace($key, $value, $handle) {}
function dba_sync($handle) {}
function dbase_add_record($dbase_identifier, $record) {}
function dbase_close($dbase_identifier) {}
function dbase_create($filename, $fields) {}
function dbase_delete_record($dbase_identifier, $record_number) {}
function dbase_get_header_info($dbase_identifier) {}
function dbase_get_record_with_names($dbase_identifier, $record_number) {}
function dbase_get_record($dbase_identifier, $record_number) {}
function dbase_numfields($dbase_identifier) {}
function dbase_numrecords($dbase_identifier) {}
function dbase_open($filename, $mode) {}
function dbase_pack($dbase_identifier) {}
function dbase_replace_record($dbase_identifier, $record, $record_number) {}
function dbplus_add($relation, $tuple) {}
function dbplus_aql($query, $server, $dbpath) {}
function dbplus_chdir($newdir) {}
function dbplus_close($relation) {}
function dbplus_curr($relation, $tuple) {}
function dbplus_errcode($errno) {}
function dbplus_errno() {}
function dbplus_find($relation, $constraints, $tuple) {}
function dbplus_first($relation, $tuple) {}
function dbplus_flush($relation) {}
function dbplus_freealllocks() {}
function dbplus_freelock($relation, $tuple) {}
function dbplus_freerlocks($relation) {}
function dbplus_getlock($relation, $tuple) {}
function dbplus_getunique($relation, $uniqueid) {}
function dbplus_info($relation, $key, $result) {}
function dbplus_last($relation, $tuple) {}
function dbplus_lockrel($relation) {}
function dbplus_next($relation, $tuple) {}
function dbplus_open($name) {}
function dbplus_prev($relation, $tuple) {}
function dbplus_rchperm($relation, $mask, $user, $group) {}
function dbplus_rcreate($name, $domlist, $overwrite) {}
function dbplus_rcrtexact($name, $relation, $overwrite) {}
function dbplus_rcrtlike($name, $relation, $overwrite) {}
function dbplus_resolve($relation_name) {}
function dbplus_restorepos($relation, $tuple) {}
function dbplus_rkeys($relation, $domlist) {}
function dbplus_ropen($name) {}
function dbplus_rquery($query, $dbpath) {}
function dbplus_rrename($relation, $name) {}
function dbplus_rsecindex($relation, $domlist, $type) {}
function dbplus_runlink($relation) {}
function dbplus_rzap($relation) {}
function dbplus_savepos($relation) {}
function dbplus_setindex($relation, $idx_name) {}
function dbplus_setindexbynumber($relation, $idx_number) {}
function dbplus_sql($query, $server, $dbpath) {}
function dbplus_tcl($sid, $script) {}
function dbplus_tremove($relation, $tuple, $current) {}
function dbplus_undo($relation) {}
function dbplus_undoprepare($relation) {}
function dbplus_unlockrel($relation) {}
function dbplus_unselect($relation) {}
function dbplus_update($relation, $old, $new) {}
function dbplus_xlockrel($relation) {}
function dbplus_xunlockrel($relation) {}
function dbx_close($link_identifier) {}
function dbx_compare($row_a, $row_b, $column_key, $flags) {}
function dbx_connect($module, $host, $database, $username, $password, $persistent) {}
function dbx_error($link_identifier) {}
function dbx_escape_string($link_identifier, $text) {}
function dbx_fetch_row($result_identifier) {}
function dbx_query($link_identifier, $sql_statement, $flags) {}
function dbx_sort($result, $user_compare_function) {}
function dio_close($fd) {}
function dio_fcntl($fd, $cmd, $args) {}
function dio_open($filename, $flags, $mode) {}
function dio_read($fd, $len) {}
function dio_seek($fd, $pos, $whence) {}
function dio_stat($fd) {}
function dio_tcsetattr($fd, $options) {}
function dio_truncate($fd, $offset) {}
function dio_write($fd, $data, $len) {}
function chdir($directory) {}
function chroot($directory) {}
function closedir($dir_handle) {}
function getcwd() {}
function opendir($path, $context) {}
function readdir($dir_handle) {}
function rewinddir($dir_handle) {}
function scandir($directory, $sorting_order, $context) {}
function dom_import_simplexml($node) {}
function domxml_new_doc($version) {}
function domxml_open_file($filename, $mode, $error) {}
function domxml_open_mem($str, $mode, $error) {}
function domxml_version() {}
function domxml_xmltree($str) {}
function domxml_xslt_stylesheet_doc($xsl_doc) {}
function domxml_xslt_stylesheet_file($xsl_file) {}
function domxml_xslt_stylesheet($xsl_buf) {}
function domxml_xslt_version() {}
function xpath_eval_expression($xpath_context, $expression, $contextnode) {}
function xpath_eval($xpath_context, $xpath_expression, $contextnode) {}
function xpath_new_context($dom_document) {}
function xpath_register_ns_auto($xpath_context, $context_node) {}
function xpath_register_ns($xpath_context, $prefix, $uri) {}
function xptr_eval($xpath_context, $eval_str, $contextnode) {}
function xptr_new_context() {}
function dotnet_load($assembly_name, $datatype_name, $codepage) {}
function enchant_broker_describe($broker) {}
function enchant_broker_dict_exists($broker, $tag) {}
function enchant_broker_free_dict($dict) {}
function enchant_broker_free($broker) {}
function enchant_broker_get_error($broker) {}
function enchant_broker_init() {}
function enchant_broker_list_dicts($broker) {}
function enchant_broker_request_dict($broker, $tag) {}
function enchant_broker_request_pwl_dict($broker, $filename) {}
function enchant_broker_set_ordering($broker, $tag, $ordering) {}
function enchant_dict_add_to_personal($dict, $word) {}
function enchant_dict_add_to_session($dict, $word) {}
function enchant_dict_check($dict, $word) {}
function enchant_dict_describe($dict) {}
function enchant_dict_get_error($dict) {}
function enchant_dict_is_in_session($dict, $word) {}
function enchant_dict_quick_check($dict, $word, $suggestions) {}
function enchant_dict_store_replacement($dict, $mis, $cor) {}
function enchant_dict_suggest($dict, $word) {}
function debug_backtrace($provide_object) {}
function debug_print_backtrace() {}
function error_get_last() {}
function error_log($message, $message_type, $destination, $extra_headers) {}
function error_reporting($level) {}
function restore_error_handler() {}
function restore_exception_handler() {}
function set_error_handler($error_handler, $error_types) {}
function set_exception_handler($exception_handler) {}
function trigger_error($error_msg, $error_type) {}
function escapeshellarg($arg) {}
function escapeshellcmd($command) {}
function exec($command, $output, $return_var) {}
function passthru($command, $return_var) {}
function proc_close($process) {}
function proc_get_status($process) {}
function proc_nice($increment) {}
function proc_open($cmd, $descriptorspec, $pipes, $cwd, $env, $other_options) {}
function proc_terminate($process, $signal) {}
function shell_exec($cmd) {}
function system($command, $return_var) {}
function exif_imagetype($filename) {}
function exif_read_data($filename, $sections, $arrays, $thumbnail) {}
function exif_tagname($index) {}
function exif_thumbnail($filename, $width, $height, $imagetype) {}
function expect_expectl($expect, $cases, $match) {}
function expect_popen($command) {}
function fam_cancel_monitor($fam, $fam_monitor) {}
function fam_close($fam) {}
function fam_monitor_collection($fam, $dirname, $depth, $mask) {}
function fam_monitor_directory($fam, $dirname) {}
function fam_monitor_file($fam, $filename) {}
function fam_next_event($fam) {}
function fam_open($appname) {}
function fam_pending($fam) {}
function fam_resume_monitor($fam, $fam_monitor) {}
function fam_suspend_monitor($fam, $fam_monitor) {}
function fbsql_affected_rows($link_identifier) {}
function fbsql_autocommit($link_identifier, $OnOff) {}
function fbsql_blob_size($blob_handle, $link_identifier) {}
function fbsql_change_user($user, $password, $database, $link_identifier) {}
function fbsql_clob_size($clob_handle, $link_identifier) {}
function fbsql_close($link_identifier) {}
function fbsql_commit($link_identifier) {}
function fbsql_connect($hostname, $username, $password) {}
function fbsql_create_blob($blob_data, $link_identifier) {}
function fbsql_create_clob($clob_data, $link_identifier) {}
function fbsql_create_db($database_name, $link_identifier, $database_options) {}
function fbsql_data_seek($result, $row_number) {}
function fbsql_database_password($link_identifier, $database_password) {}
function fbsql_database($link_identifier, $database) {}
function fbsql_db_query($database, $query, $link_identifier) {}
function fbsql_db_status($database_name, $link_identifier) {}
function fbsql_drop_db($database_name, $link_identifier) {}
function fbsql_errno($link_identifier) {}
function fbsql_error($link_identifier) {}
function fbsql_fetch_array($result, $result_type) {}
function fbsql_fetch_assoc($result) {}
function fbsql_fetch_field($result, $field_offset) {}
function fbsql_fetch_lengths($result) {}
function fbsql_fetch_object($result) {}
function fbsql_fetch_row($result) {}
function fbsql_field_flags($result, $field_offset) {}
function fbsql_field_len($result, $field_offset) {}
function fbsql_field_name($result, $field_index) {}
function fbsql_field_seek($result, $field_offset) {}
function fbsql_field_table($result, $field_offset) {}
function fbsql_field_type($result, $field_offset) {}
function fbsql_free_result($result) {}
function fbsql_get_autostart_info($link_identifier) {}
function fbsql_hostname($link_identifier, $host_name) {}
function fbsql_insert_id($link_identifier) {}
function fbsql_list_dbs($link_identifier) {}
function fbsql_list_fields($database_name, $table_name, $link_identifier) {}
function fbsql_list_tables($database, $link_identifier) {}
function fbsql_next_result($result) {}
function fbsql_num_fields($result) {}
function fbsql_num_rows($result) {}
function fbsql_password($link_identifier, $password) {}
function fbsql_pconnect($hostname, $username, $password) {}
function fbsql_query($query, $link_identifier, $batch_size) {}
function fbsql_read_blob($blob_handle, $link_identifier) {}
function fbsql_read_clob($clob_handle, $link_identifier) {}
function fbsql_result($result, $row, $field) {}
function fbsql_rollback($link_identifier) {}
function fbsql_rows_fetched($result) {}
function fbsql_select_db($database_name, $link_identifier) {}
function fbsql_set_characterset($link_identifier, $characterset, $in_out_both) {}
function fbsql_set_lob_mode($result, $lob_mode) {}
function fbsql_set_password($link_identifier, $user, $password, $old_password) {}
function fbsql_set_transaction($link_identifier, $locking, $isolation) {}
function fbsql_start_db($database_name, $link_identifier, $database_options) {}
function fbsql_stop_db($database_name, $link_identifier) {}
function fbsql_table_name($result, $index) {}
function fbsql_username($link_identifier, $username) {}
function fbsql_warnings($OnOff) {}
function fdf_add_doc_javascript($fdf_document, $script_name, $script_code) {}
function fdf_add_template($fdf_document, $newpage, $filename, $template, $rename) {}
function fdf_close($fdf_document) {}
function fdf_create() {}
function fdf_enum_values($fdf_document, $function, $userdata) {}
function fdf_errno() {}
function fdf_error($error_code) {}
function fdf_get_ap($fdf_document, $field, $face, $filename) {}
function fdf_get_attachment($fdf_document, $fieldname, $savepath) {}
function fdf_get_encoding($fdf_document) {}
function fdf_get_file($fdf_document) {}
function fdf_get_flags($fdf_document, $fieldname, $whichflags) {}
function fdf_get_opt($fdf_document, $fieldname, $element) {}
function fdf_get_status($fdf_document) {}
function fdf_get_value($fdf_document, $fieldname, $which) {}
function fdf_get_version($fdf_document) {}
function fdf_header() {}
function fdf_next_field_name($fdf_document, $fieldname) {}
function fdf_open_string($fdf_data) {}
function fdf_open($filename) {}
function fdf_remove_item($fdf_document, $fieldname, $item) {}
function fdf_save_string($fdf_document) {}
function fdf_save($fdf_document, $filename) {}
function fdf_set_ap($fdf_document, $field_name, $face, $filename, $page_number) {}
function fdf_set_encoding($fdf_document, $encoding) {}
function fdf_set_file($fdf_document, $url, $target_frame) {}
function fdf_set_flags($fdf_document, $fieldname, $whichFlags, $newFlags) {}
function fdf_set_javascript_action($fdf_document, $fieldname, $trigger, $script) {}
function fdf_set_on_import_javascript($fdf_document, $script, $before_data_import) {}
function fdf_set_opt($fdf_document, $fieldname, $element, $str1, $str2) {}
function fdf_set_status($fdf_document, $status) {}
function fdf_set_submit_form_action($fdf_document, $fieldname, $trigger, $script, $flags) {}
function fdf_set_target_frame($fdf_document, $frame_name) {}
function fdf_set_value($fdf_document, $fieldname, $value, $isName) {}
function fdf_set_version($fdf_document, $version) {}
function finfo_buffer($finfo, $string, $options, $context) {}
function finfo_close($finfo) {}
function finfo_file($finfo, $file_name, $options, $context) {}
function finfo_open($options, $arg) {}
function finfo_set_flags($finfo, $options) {}
function filepro_fieldcount() {}
function filepro_fieldname($field_number) {}
function filepro_fieldtype($field_number) {}
function filepro_fieldwidth($field_number) {}
function filepro_retrieve($row_number, $field_number) {}
function filepro_rowcount() {}
function filepro($directory) {}
function basename($path, $suffix) {}
function chgrp($filename, $group) {}
function chmod($filename, $mode) {}
function chown($filename, $user) {}
function clearstatcache() {}
function copy($source, $dest, $context) {}
function delete() {}
function dirname($path) {}
function disk_free_space($directory) {}
function disk_total_space($directory) {}
function fclose($handle) {}
function feof($handle) {}
function fflush($handle) {}
function fgetc($handle) {}
function fgetcsv($handle, $length, $delimiter, $enclosure, $escape) {}
function fgets($handle, $length) {}
function fgetss($handle, $length, $allowable_tags) {}
function file_exists($filename) {}
function file_get_contents($filename, $flags, $context, $offset, $maxlen) {}
function file_put_contents($filename, $data, $flags, $context) {}
function file($filename, $flags, $context) {}
function fileatime($filename) {}
function filectime($filename) {}
function filegroup($filename) {}
function fileinode($filename) {}
function filemtime($filename) {}
function fileowner($filename) {}
function fileperms($filename) {}
function filesize($filename) {}
function filetype($filename) {}
function flock($handle, $operation, $wouldblock) {}
function fnmatch($pattern, $string, $flags) {}
function fopen($filename, $mode, $use_include_path, $context) {}
function fpassthru($handle) {}
function fputcsv($handle, $fields, $delimiter, $enclosure) {}
function fread($handle, $length) {}
function fscanf($handle, $format) {}
function fseek($handle, $offset, $whence) {}
function fstat($handle) {}
function ftell($handle) {}
function ftruncate($handle, $size) {}
function fwrite($handle, $string, $length) {}
function glob($pattern, $flags) {}
function is_dir($filename) {}
function is_executable($filename) {}
function is_file($filename) {}
function is_link($filename) {}
function is_readable($filename) {}
function is_uploaded_file($filename) {}
function is_writable($filename) {}
function lchgrp($filename, $group) {}
function lchown($filename, $user) {}
function link($target, $link) {}
function linkinfo($path) {}
function lstat($filename) {}
function mkdir($pathname, $mode, $recursive, $context) {}
function move_uploaded_file($filename, $destination) {}
function parse_ini_file($filename, $process_sections) {}
function pathinfo($path, $options) {}
function pclose($handle) {}
function popen($command, $mode) {}
function readfile($filename, $use_include_path, $context) {}
function readlink($path) {}
function realpath($path) {}
function rename($oldname, $newname, $context) {}
function rewind($handle) {}
function rmdir($dirname, $context) {}
function stat($filename) {}
function symlink($target, $link) {}
function tempnam($dir, $prefix) {}
function tmpfile() {}
function touch($filename, $time, $atime) {}
function umask($mask) {}
function unlink($filename, $context) {}
function filter_has_var($type, $variable_name) {}
function filter_id($filtername) {}
function filter_input_array($type, $definition) {}
function filter_input($type, $variable_name, $filter, $options) {}
function filter_list() {}
function filter_var_array($data, $definition) {}
function filter_var($variable, $filter, $options) {}
function fribidi_log2vis($str, $direction, $charset) {}
function ftp_alloc($ftp_stream, $filesize, $result) {}
function ftp_cdup($ftp_stream) {}
function ftp_chdir($ftp_stream, $directory) {}
function ftp_chmod($ftp_stream, $mode, $filename) {}
function ftp_close($ftp_stream) {}
function ftp_connect($host, $port, $timeout) {}
function ftp_delete($ftp_stream, $path) {}
function ftp_exec($ftp_stream, $command) {}
function ftp_fget($ftp_stream, $handle, $remote_file, $mode, $resumepos) {}
function ftp_fput($ftp_stream, $remote_file, $handle, $mode, $startpos) {}
function ftp_get_option($ftp_stream, $option) {}
function ftp_get($ftp_stream, $local_file, $remote_file, $mode, $resumepos) {}
function ftp_login($ftp_stream, $username, $password) {}
function ftp_mdtm($ftp_stream, $remote_file) {}
function ftp_mkdir($ftp_stream, $directory) {}
function ftp_nb_continue($ftp_stream) {}
function ftp_nb_fget($ftp_stream, $handle, $remote_file, $mode, $resumepos) {}
function ftp_nb_fput($ftp_stream, $remote_file, $handle, $mode, $startpos) {}
function ftp_nb_get($ftp_stream, $local_file, $remote_file, $mode, $resumepos) {}
function ftp_nb_put($ftp_stream, $remote_file, $local_file, $mode, $startpos) {}
function ftp_nlist($ftp_stream, $directory) {}
function ftp_pasv($ftp_stream, $pasv) {}
function ftp_put($ftp_stream, $remote_file, $local_file, $mode, $startpos) {}
function ftp_pwd($ftp_stream) {}
function ftp_raw($ftp_stream, $command) {}
function ftp_rawlist($ftp_stream, $directory, $recursive) {}
function ftp_rename($ftp_stream, $oldname, $newname) {}
function ftp_rmdir($ftp_stream, $directory) {}
function ftp_set_option($ftp_stream, $option, $value) {}
function ftp_site($ftp_stream, $command) {}
function ftp_size($ftp_stream, $remote_file) {}
function ftp_ssl_connect($host, $port, $timeout) {}
function ftp_systype($ftp_stream) {}
function call_user_func_array($function, $param_arr) {}
function call_user_func($function, $parameter) {}
function create_function($args, $code) {}
function func_get_arg($arg_num) {}
function func_get_args() {}
function func_num_args() {}
function function_exists($function_name) {}
function get_defined_functions() {}
function register_shutdown_function($function, $parameter) {}
function register_tick_function($function, $arg) {}
function unregister_tick_function($function_name) {}
function geoip_country_code_by_name($hostname) {}
function geoip_country_code3_by_name($hostname) {}
function geoip_country_name_by_name($hostname) {}
function geoip_database_info($database) {}
function geoip_db_avail($database) {}
function geoip_db_filename($database) {}
function geoip_db_get_all_info() {}
function geoip_id_by_name($hostname) {}
function geoip_isp_by_name($hostname) {}
function geoip_org_by_name($hostname) {}
function geoip_record_by_name($hostname) {}
function geoip_region_by_name($hostname) {}
function bind_textdomain_codeset($domain, $codeset) {}
function bindtextdomain($domain, $directory) {}
function dcgettext($domain, $message, $category) {}
function dcngettext($domain, $msgid1, $msgid2, $n, $category) {}
function dgettext($domain, $message) {}
function dngettext($domain, $msgid1, $msgid2, $n) {}
function gettext($message) {}
function ngettext($msgid1, $msgid2, $n) {}
function textdomain($text_domain) {}
function gmp_abs($a) {}
function gmp_add($a, $b) {}
function gmp_and($a, $b) {}
function gmp_clrbit($a, $index) {}
function gmp_cmp($a, $b) {}
function gmp_com($a) {}
function gmp_div_q($a, $b, $round) {}
function gmp_div_qr($n, $d, $round) {}
function gmp_div_r($n, $d, $round) {}
function gmp_divexact($n, $d) {}
function gmp_fact($a) {}
function gmp_gcd($a, $b) {}
function gmp_gcdext($a, $b) {}
function gmp_hamdist($a, $b) {}
function gmp_init($number, $base) {}
function gmp_intval($gmpnumber) {}
function gmp_invert($a, $b) {}
function gmp_jacobi($a, $p) {}
function gmp_legendre($a, $p) {}
function gmp_mod($n, $d) {}
function gmp_mul($a, $b) {}
function gmp_neg($a) {}
function gmp_nextprime($a) {}
function gmp_or($a, $b) {}
function gmp_perfect_square($a) {}
function gmp_popcount($a) {}
function gmp_pow($base, $exp) {}
function gmp_powm($base, $exp, $mod) {}
function gmp_prob_prime($a, $reps) {}
function gmp_random($limiter) {}
function gmp_scan0($a, $start) {}
function gmp_scan1($a, $start) {}
function gmp_setbit($a, $index, $set_clear) {}
function gmp_sign($a) {}
function gmp_sqrt($a) {}
function gmp_sqrtrem($a) {}
function gmp_strval($gmpnumber, $base) {}
function gmp_sub($a, $b) {}
function gmp_testbit($a, $index) {}
function gmp_xor($a, $b) {}
function gnupg_adddecryptkey($identifier, $fingerprint, $passphrase) {}
function gnupg_addencryptkey($identifier, $fingerprint) {}
function gnupg_addsignkey($identifier, $fingerprint, $passphrase) {}
function gnupg_cleardecryptkeys($identifier) {}
function gnupg_clearencryptkeys($identifier) {}
function gnupg_clearsignkeys($identifier) {}
function gnupg_decrypt($identifier, $text) {}
function gnupg_decryptverify($identifier, $text, $plaintext) {}
function gnupg_encrypt($identifier, $plaintext) {}
function gnupg_encryptsign($identifier, $plaintext) {}
function gnupg_export($identifier, $fingerprint) {}
function gnupg_geterror($identifier) {}
function gnupg_getprotocol($identifier) {}
function gnupg_import($identifier, $keydata) {}
function gnupg_init() {}
function gnupg_keyinfo($identifier, $pattern) {}
function gnupg_setarmor($identifier, $armor) {}
function gnupg_seterrormode($identifier, $errormode) {}
function gnupg_setsignmode($identifier, $signmode) {}
function gnupg_sign($identifier, $plaintext) {}
function gnupg_verify($identifier, $signed_text, $signature, $plaintext) {}
function hash_algos() {}
function hash_copy($context) {}
function hash_file($algo, $filename, $raw_output) {}
function hash_final($context, $raw_output) {}
function hash_hmac_file($algo, $filename, $key, $raw_output) {}
function hash_hmac($algo, $data, $key, $raw_output) {}
function hash_init($algo, $options, $key) {}
function hash_update_file($context, $filename, $context) {}
function hash_update_stream($context, $handle, $length) {}
function hash_update($context, $data) {}
function hash($algo, $data, $raw_output) {}
function http_cache_etag($etag) {}
function http_cache_last_modified($timestamp_or_expires) {}
function http_chunked_decode($encoded) {}
function http_deflate($data, $flags = 0) {}
function http_inflate($data) {}
function http_build_cookie($cookie) {}
function http_date($timestamp) {}
function http_get_request_body_stream() {}
function http_get_request_body() {}
function http_get_request_headers() {}
function http_match_etag($etag, $for_range = FALSE) {}
function http_match_modified($timestamp, $for_range = FALSE) {}
function http_match_request_header($header, $value, $match_case = FALSE) {}
function http_support($feature = 0) {}
function http_negotiate_charset($supported, $result) {}
function http_negotiate_content_type($supported, $result) {}
function http_negotiate_language($supported, $result) {}
function ob_deflatehandler($data, $mode) {}
function ob_etaghandler($data, $mode) {}
function ob_inflatehandler($data, $mode) {}
function http_parse_cookie($cookie, $flags, $allowed_extras) {}
function http_parse_headers($header) {}
function http_parse_message($message) {}
function http_parse_params($param, $flags = HTTP_PARAMS_DEFAULT) {}
function http_persistent_handles_clean($ident) {}
function http_persistent_handles_count() {}
function http_persistent_handles_ident($ident) {}
function http_get($url, $options, $info) {}
function http_head($url, $options, $info) {}
function http_post_data($url, $data, $options, $info) {}
function http_post_fields($url, $data, $files, $options, $info) {}
function http_put_data($url, $data, $options, $info) {}
function http_put_file($url, $file, $options, $info) {}
function http_put_stream($url, $stream, $options, $info) {}
function http_request_body_encode($fields, $files) {}
function http_request_method_exists($method) {}
function http_request_method_name($method) {}
function http_request_method_register($method) {}
function http_request_method_unregister($method) {}
function http_request($method, $url, $body, $options, $info) {}
function http_redirect($url, $params, $session = FALSE, $status) {}
function http_send_content_disposition($filename, $inline = FALSE) {}
function http_send_content_type($content_type = 'applicationxoctetstream') {}
function http_send_data($data) {}
function http_send_file($file) {}
function http_send_last_modified($timestamp) {}
function http_send_status($status) {}
function http_send_stream($stream) {}
function http_throttle($sec, $bytes = 40960) {}
function http_build_str($query, $prefix, $arg_separator) {}
function http_build_url($url, $parts, $flags = HTTP_URL_REPLACE, $new_url) {}
function hw_array2objrec($object_array) {}
function hw_changeobject($link, $objid, $attributes) {}
function hw_children($connection, $objectID) {}
function hw_childrenobj($connection, $objectID) {}
function hw_close($connection) {}
function hw_connect($host, $port, $username, $password) {}
function hw_connection_info($link) {}
function hw_cp($connection, $object_id_array, $destination_id) {}
function hw_deleteobject($connection, $object_to_delete) {}
function hw_docbyanchor($connection, $anchorID) {}
function hw_docbyanchorobj($connection, $anchorID) {}
function hw_document_attributes($hw_document) {}
function hw_document_bodytag($hw_document, $prefix) {}
function hw_document_content($hw_document) {}
function hw_document_setcontent($hw_document, $content) {}
function hw_document_size($hw_document) {}
function hw_dummy($link, $id, $msgid) {}
function hw_edittext($connection, $hw_document) {}
function hw_error($connection) {}
function hw_errormsg($connection) {}
function hw_free_document($hw_document) {}
function hw_getanchors($connection, $objectID) {}
function hw_getanchorsobj($connection, $objectID) {}
function hw_getandlock($connection, $objectID) {}
function hw_getchildcoll($connection, $objectID) {}
function hw_getchildcollobj($connection, $objectID) {}
function hw_getchilddoccoll($connection, $objectID) {}
function hw_getchilddoccollobj($connection, $objectID) {}
function hw_getobject($connection, $objectID, $query) {}
function hw_getobjectbyquery($connection, $query, $max_hits) {}
function hw_getobjectbyquerycoll($connection, $objectID, $query, $max_hits) {}
function hw_getobjectbyquerycollobj($connection, $objectID, $query, $max_hits) {}
function hw_getobjectbyqueryobj($connection, $query, $max_hits) {}
function hw_getparents($connection, $objectID) {}
function hw_getparentsobj($connection, $objectID) {}
function hw_getrellink($link, $rootid, $sourceid, $destid) {}
function hw_getremote($connection, $objectID) {}
function hw_getremotechildren($connection, $object_record) {}
function hw_getsrcbydestobj($connection, $objectID) {}
function hw_gettext($connection, $objectID, $rootIDprefix) {}
function hw_getusername($connection) {}
function hw_identify($link, $username, $password) {}
function hw_incollections($connection, $object_id_array, $collection_id_array, $return_collections) {}
function hw_info($connection) {}
function hw_inscoll($connection, $objectID, $object_array) {}
function hw_insdoc($connection, $parentID, $object_record, $text) {}
function hw_insertanchors($hwdoc, $anchorecs, $dest, $urlprefixes) {}
function hw_insertdocument($connection, $parent_id, $hw_document) {}
function hw_insertobject($connection, $object_rec, $parameter) {}
function hw_mapid($connection, $server_id, $object_id) {}
function hw_modifyobject($connection, $object_to_change, $remove, $add, $mode) {}
function hw_mv($connection, $object_id_array, $source_id, $destination_id) {}
function hw_new_document($object_record, $document_data, $document_size) {}
function hw_objrec2array($object_record, $format) {}
function hw_output_document($hw_document) {}
function hw_pconnect($host, $port, $username, $password) {}
function hw_pipedocument($connection, $objectID, $url_prefixes) {}
function hw_root() {}
function hw_setlinkroot($link, $rootid) {}
function hw_stat($link) {}
function hw_unlock($connection, $objectID) {}
function hw_who($connection) {}
function hw_api_attribute($name, $value) {}
function hwapi_hgcsp($hostname, $port) {}
function hw_api_content($content, $mimetype) {}
function hw_api_object($parameter) {}
function locale_get_default() {}
function locale_set_default($name) {}
function ibase_add_user($service_handle, $user_name, $password, $first_name, $middle_name, $last_name) {}
function ibase_affected_rows($link_identifier) {}
function ibase_backup($service_handle, $source_db, $dest_file, $options, $verbose) {}
function ibase_blob_add($blob_handle, $data) {}
function ibase_blob_cancel($blob_handle) {}
function ibase_blob_close($blob_handle) {}
function ibase_blob_create($link_identifier) {}
function ibase_blob_echo($link_identifier, $blob_id) {}
function ibase_blob_get($blob_handle, $len) {}
function ibase_blob_import($link_identifier, $file_handle) {}
function ibase_blob_info($link_identifier, $blob_id) {}
function ibase_blob_open($link_identifier, $blob_id) {}
function ibase_close($connection_id) {}
function ibase_commit_ret($link_or_trans_identifier) {}
function ibase_commit($link_or_trans_identifier) {}
function ibase_connect($database, $username, $password, $charset, $buffers, $dialect, $role, $sync) {}
function ibase_db_info($service_handle, $db, $action, $argument) {}
function ibase_delete_user($service_handle, $user_name) {}
function ibase_drop_db($connection) {}
function ibase_errcode() {}
function ibase_errmsg() {}
function ibase_execute($query, $bind_arg) {}
function ibase_fetch_assoc($result, $fetch_flag) {}
function ibase_fetch_object($result_id, $fetch_flag) {}
function ibase_fetch_row($result_identifier, $fetch_flag) {}
function ibase_field_info($result, $field_number) {}
function ibase_free_event_handler($event) {}
function ibase_free_query($query) {}
function ibase_free_result($result_identifier) {}
function ibase_gen_id($generator, $increment, $link_identifier) {}
function ibase_maintain_db($service_handle, $db, $action, $argument) {}
function ibase_modify_user($service_handle, $user_name, $password, $first_name, $middle_name, $last_name) {}
function ibase_name_result($result, $name) {}
function ibase_num_fields($result_id) {}
function ibase_num_params($query) {}
function ibase_param_info($query, $param_number) {}
function ibase_pconnect($database, $username, $password, $charset, $buffers, $dialect, $role, $sync) {}
function ibase_prepare($query) {}
function ibase_query($link_identifier, $query, $bind_args) {}
function ibase_restore($service_handle, $source_file, $dest_db, $options, $verbose) {}
function ibase_rollback_ret($link_or_trans_identifier) {}
function ibase_rollback($link_or_trans_identifier) {}
function ibase_server_info($service_handle, $action) {}
function ibase_service_attach($host, $dba_username, $dba_password) {}
function ibase_service_detach($service_handle) {}
function ibase_set_event_handler($event_handler, $event_name1, $event_name2) {}
function ibase_timefmt($format, $columntype) {}
function ibase_trans($trans_args, $link_identifier) {}
function ibase_wait_event($event_name1, $event_name2) {}
function db2_autocommit($connection, $value) {}
function db2_bind_param($stmt, $parameternumber, $variablename, $parametertype, $datatype, $precision, $scale) {}
function db2_client_info($connection) {}
function db2_close($connection) {}
function db2_column_privileges($connection, $qualifier, $schema, $tablename, $columnname) {}
function db2_columns($connection, $qualifier, $schema, $tablename, $columnname) {}
function db2_commit($connection) {}
function db2_conn_error($connection) {}
function db2_conn_errormsg($connection) {}
function db2_connect($database, $username, $password, $options) {}
function db2_cursor_type($stmt) {}
function db2_escape_string($string_literal) {}
function db2_exec($connection, $statement, $options) {}
function db2_execute($stmt, $parameters) {}
function db2_fetch_array($stmt, $row_number) {}
function db2_fetch_assoc($stmt, $row_number) {}
function db2_fetch_both($stmt, $row_number) {}
function db2_fetch_object($stmt, $row_number) {}
function db2_fetch_row($stmt, $row_number) {}
function db2_field_display_size($stmt, $column) {}
function db2_field_name($stmt, $column) {}
function db2_field_num($stmt, $column) {}
function db2_field_precision($stmt, $column) {}
function db2_field_scale($stmt, $column) {}
function db2_field_type($stmt, $column) {}
function db2_field_width($stmt, $column) {}
function db2_foreign_keys($connection, $qualifier, $schema, $tablename) {}
function db2_free_result($stmt) {}
function db2_free_stmt($stmt) {}
function db2_get_option($resource, $option) {}
function db2_lob_read($stmt, $colnum, $length) {}
function db2_next_result($stmt) {}
function db2_num_fields($stmt) {}
function db2_num_rows($stmt) {}
function db2_pconnect($database, $username, $password, $options) {}
function db2_prepare($connection, $statement, $options) {}
function db2_primary_keys($connection, $qualifier, $schema, $tablename) {}
function db2_procedure_columns($connection, $qualifier, $schema, $procedure, $parameter) {}
function db2_procedures($connection, $qualifier, $schema, $procedure) {}
function db2_result($stmt, $column) {}
function db2_rollback($connection) {}
function db2_server_info($connection) {}
function db2_set_option($resource, $options, $type) {}
function db2_special_columns($connection, $qualifier, $schema, $table_name, $scope) {}
function db2_statistics($connection, $qualifier, $schema, $tablename, $unique) {}
function db2_stmt_error($stmt) {}
function db2_stmt_errormsg($stmt) {}
function db2_table_privileges($connection, $qualifier, $schema, $table_name) {}
function db2_tables($connection, $qualifier, $schema, $tablename, $tabletype) {}
function iconv_get_encoding($type) {}
function iconv_mime_decode_headers($encoded_headers, $mode, $charset) {}
function iconv_mime_decode($encoded_header, $mode, $charset) {}
function iconv_mime_encode($field_name, $field_value, $preferences) {}
function iconv_set_encoding($type, $charset) {}
function iconv_strlen($str, $charset) {}
function iconv_strpos($haystack, $needle, $offset, $charset) {}
function iconv_strrpos($haystack, $needle, $charset) {}
function iconv_substr($str, $offset) {}
function iconv($in_charset, $out_charset, $str) {}
function ob_iconv_handler($contents, $status) {}
function id3_get_frame_long_name($frameId) {}
function id3_get_frame_short_name($frameId) {}
function id3_get_genre_id($genre) {}
function id3_get_genre_list() {}
function id3_get_genre_name($genre_id) {}
function id3_get_tag($filename, $version) {}
function id3_get_version($filename) {}
function id3_remove_tag($filename, $version) {}
function id3_set_tag($filename, $tag, $version) {}
function ifx_affected_rows($result_id) {}
function ifx_blobinfile_mode($mode) {}
function ifx_byteasvarchar($mode) {}
function ifx_close($link_identifier) {}
function ifx_connect($database, $userid, $password) {}
function ifx_copy_blob($bid) {}
function ifx_create_blob($type, $mode, $param) {}
function ifx_create_char($param) {}
function ifx_do($result_id) {}
function ifx_error($link_identifier) {}
function ifx_errormsg($errorcode) {}
function ifx_fetch_row($result_id, $position) {}
function ifx_fieldproperties($result_id) {}
function ifx_fieldtypes($result_id) {}
function ifx_free_blob($bid) {}
function ifx_free_char($bid) {}
function ifx_free_result($result_id) {}
function ifx_get_blob($bid) {}
function ifx_get_char($bid) {}
function ifx_getsqlca($result_id) {}
function ifx_htmltbl_result($result_id, $html_table_options) {}
function ifx_nullformat($mode) {}
function ifx_num_fields($result_id) {}
function ifx_num_rows($result_id) {}
function ifx_pconnect($database, $userid, $password) {}
function ifx_prepare($query, $link_identifier, $cursor_def, $blobidarray) {}
function ifx_query($query, $link_identifier, $cursor_type, $blobidarray) {}
function ifx_textasvarchar($mode) {}
function ifx_update_blob($bid, $content) {}
function ifx_update_char($bid, $content) {}
function ifxus_close_slob($bid) {}
function ifxus_create_slob($mode) {}
function ifxus_free_slob($bid) {}
function ifxus_open_slob($bid, $mode) {}
function ifxus_read_slob($bid, $nbytes) {}
function ifxus_seek_slob($bid, $mode, $offset) {}
function ifxus_tell_slob($bid) {}
function ifxus_write_slob($bid, $content) {}
function iis_add_server($path, $comment, $server_ip, $port, $host_name, $rights, $start_server) {}
function iis_get_dir_security($server_instance, $virtual_path) {}
function iis_get_script_map($server_instance, $virtual_path, $script_extension) {}
function iis_get_server_by_comment($comment) {}
function iis_get_server_by_path($path) {}
function iis_get_server_rights($server_instance, $virtual_path) {}
function iis_get_service_state($service_id) {}
function iis_remove_server($server_instance) {}
function iis_set_app_settings($server_instance, $virtual_path, $application_scope) {}
function iis_set_dir_security($server_instance, $virtual_path, $directory_flags) {}
function iis_set_script_map($server_instance, $virtual_path, $script_extension, $engine_path, $allow_scripting) {}
function iis_set_server_rights($server_instance, $virtual_path, $directory_flags) {}
function iis_start_server($server_instance) {}
function iis_start_service($service_id) {}
function iis_stop_server($server_instance) {}
function iis_stop_service($service_id) {}
function gd_info() {}
function getimagesize($filename, $imageinfo) {}
function image_type_to_extension($imagetype, $include_dot) {}
function image_type_to_mime_type($imagetype) {}
function image2wbmp($image, $filename, $threshold) {}
function imagealphablending($image, $blendmode) {}
function imageantialias($image, $enabled) {}
function imagearc($image, $cx, $cy, $width, $height, $start, $end, $color) {}
function imagechar($image, $font, $x, $y, $c, $color) {}
function imagecharup($image, $font, $x, $y, $c, $color) {}
function imagecolorallocate($image, $red, $green, $blue) {}
function imagecolorallocatealpha($image, $red, $green, $blue, $alpha) {}
function imagecolorat($image, $x, $y) {}
function imagecolorclosest($image, $red, $green, $blue) {}
function imagecolorclosestalpha($image, $red, $green, $blue, $alpha) {}
function imagecolorclosesthwb($image, $red, $green, $blue) {}
function imagecolordeallocate($image, $color) {}
function imagecolorexact($image, $red, $green, $blue) {}
function imagecolorexactalpha($image, $red, $green, $blue, $alpha) {}
function imagecolormatch($image1, $image2) {}
function imagecolorresolve($image, $red, $green, $blue) {}
function imagecolorresolvealpha($image, $red, $green, $blue, $alpha) {}
function imagecolorset($image, $index, $red, $green, $blue) {}
function imagecolorsforindex($image, $index) {}
function imagecolorstotal($image) {}
function imagecolortransparent($image, $color) {}
function imageconvolution($image, $matrix, $div, $offset) {}
function imagecopy($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h) {}
function imagecopymerge($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h, $pct) {}
function imagecopymergegray($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h, $pct) {}
function imagecopyresampled($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h) {}
function imagecopyresized($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h) {}
function imagecreate($width, $height) {}
function imagecreatefromgd($filename) {}
function imagecreatefromgd2($filename) {}
function imagecreatefromgd2part($filename, $srcX, $srcY, $width, $height) {}
function imagecreatefromgif($filename) {}
function imagecreatefromjpeg($filename) {}
function imagecreatefrompng($filename) {}
function imagecreatefromstring($data) {}
function imagecreatefromwbmp($filename) {}
function imagecreatefromxbm($filename) {}
function imagecreatefromxpm($filename) {}
function imagecreatetruecolor($width, $height) {}
function imagedashedline($image, $x1, $y1, $x2, $y2, $color) {}
function imagedestroy($image) {}
function imageellipse($image, $cx, $cy, $width, $height, $color) {}
function imagefill($image, $x, $y, $color) {}
function imagefilledarc($image, $cx, $cy, $width, $height, $start, $end, $color, $style) {}
function imagefilledellipse($image, $cx, $cy, $width, $height, $color) {}
function imagefilledpolygon($image, $points, $num_points, $color) {}
function imagefilledrectangle($image, $x1, $y1, $x2, $y2, $color) {}
function imagefilltoborder($image, $x, $y, $border, $color) {}
function imagefilter($image, $filtertype, $arg1, $arg2, $arg3, $arg4) {}
function imagefontheight($font) {}
function imagefontwidth($font) {}
function imageftbbox($size, $angle, $fontfile, $text, $extrainfo) {}
function imagefttext($image, $size, $angle, $x, $y, $color, $fontfile, $text, $extrainfo) {}
function imagegammacorrect($image, $inputgamma, $outputgamma) {}
function imagegd($image, $filename) {}
function imagegd2($image, $filename, $chunk_size, $type) {}
function imagegif($image, $filename) {}
function imagegrabscreen() {}
function imagegrabwindow($window, $client_area) {}
function imageinterlace($image, $interlace) {}
function imageistruecolor($image) {}
function imagejpeg($image, $filename, $quality) {}
function imagelayereffect($image, $effect) {}
function imageline($image, $x1, $y1, $x2, $y2, $color) {}
function imageloadfont($file) {}
function imagepalettecopy($destination, $source) {}
function imagepng($image, $filename, $quality, $filters) {}
function imagepolygon($image, $points, $num_points, $color) {}
function imagepsbbox($text, $font, $size) {}
function imagepsencodefont($font_index, $encodingfile) {}
function imagepsextendfont($font_index, $extend) {}
function imagepsfreefont($font_index) {}
function imagepsloadfont($filename) {}
function imagepsslantfont($font_index, $slant) {}
function imagepstext($image, $text, $font_index, $size, $foreground, $background, $x, $y, $space, $tightness, $angle, $antialias_steps) {}
function imagerectangle($image, $x1, $y1, $x2, $y2, $color) {}
function imagerotate($image, $angle, $bgd_color, $ignore_transparent) {}
function imagesavealpha($image, $saveflag) {}
function imagesetbrush($image, $brush) {}
function imagesetpixel($image, $x, $y, $color) {}
function imagesetstyle($image, $style) {}
function imagesetthickness($image, $thickness) {}
function imagesettile($image, $tile) {}
function imagestring($image, $font, $x, $y, $string, $color) {}
function imagestringup($image, $font, $x, $y, $string, $color) {}
function imagesx($image) {}
function imagesy($image) {}
function imagetruecolortopalette($image, $dither, $ncolors) {}
function imagettfbbox($size, $angle, $fontfile, $text) {}
function imagettftext($image, $size, $angle, $x, $y, $color, $fontfile, $text) {}
function imagetypes() {}
function imagewbmp($image, $filename, $foreground) {}
function imagexbm($image, $filename, $foreground) {}
function iptcembed($iptcdata, $jpeg_file_name, $spool) {}
function iptcparse($iptcblock) {}
function jpeg2wbmp($jpegname, $wbmpname, $dest_height, $dest_width, $threshold) {}
function png2wbmp($pngname, $wbmpname, $dest_height, $dest_width, $threshold) {}
function imap_8bit($string) {}
function imap_alerts() {}
function imap_append($imap_stream, $mailbox, $message, $options) {}
function imap_base64($text) {}
function imap_binary($string) {}
function imap_body($imap_stream, $msg_number, $options) {}
function imap_bodystruct($imap_stream, $msg_number, $section) {}
function imap_check($imap_stream) {}
function imap_clearflag_full($imap_stream, $sequence, $flag, $options) {}
function imap_close($imap_stream, $flag) {}
function imap_createmailbox($imap_stream, $mailbox) {}
function imap_delete($imap_stream, $msg_number, $options) {}
function imap_deletemailbox($imap_stream, $mailbox) {}
function imap_errors() {}
function imap_expunge($imap_stream) {}
function imap_fetch_overview($imap_stream, $sequence, $options) {}
function imap_fetchbody($imap_stream, $msg_number, $part_number, $options) {}
function imap_fetchheader($imap_stream, $msg_number, $options) {}
function imap_fetchstructure($imap_stream, $msg_number, $options) {}
function imap_get_quota($imap_stream, $quota_root) {}
function imap_get_quotaroot($imap_stream, $quota_root) {}
function imap_getacl($imap_stream, $mailbox) {}
function imap_getmailboxes($imap_stream, $ref, $pattern) {}
function imap_getsubscribed($imap_stream, $ref, $pattern) {}
function imap_headerinfo($imap_stream, $msg_number, $fromlength, $subjectlength, $defaulthost) {}
function imap_headers($imap_stream) {}
function imap_last_error() {}
function imap_list($imap_stream, $ref, $pattern) {}
function imap_listscan($imap_stream, $ref, $pattern, $content) {}
function imap_lsub($imap_stream, $ref, $pattern) {}
function imap_mail_compose($envelope, $body) {}
function imap_mail_copy($imap_stream, $msglist, $mailbox, $options) {}
function imap_mail_move($imap_stream, $msglist, $mailbox, $options) {}
function imap_mail($to, $subject, $message, $additional_headers, $cc, $bcc, $rpath) {}
function imap_mailboxmsginfo($imap_stream) {}
function imap_mime_header_decode($text) {}
function imap_msgno($imap_stream, $uid) {}
function imap_num_msg($imap_stream) {}
function imap_num_recent($imap_stream) {}
function imap_open($mailbox, $username, $password, $options, $n_retries) {}
function imap_ping($imap_stream) {}
function imap_qprint($string) {}
function imap_renamemailbox($imap_stream, $old_mbox, $new_mbox) {}
function imap_reopen($imap_stream, $mailbox, $options, $n_retries) {}
function imap_rfc822_parse_adrlist($address, $default_host) {}
function imap_rfc822_parse_headers($headers, $defaulthost) {}
function imap_rfc822_write_address($mailbox, $host, $personal) {}
function imap_savebody($imap_stream, $file, $msg_number, $part_number, $options) {}
function imap_search($imap_stream, $criteria, $options, $charset) {}
function imap_set_quota($imap_stream, $quota_root, $quota_limit) {}
function imap_setacl($imap_stream, $mailbox, $id, $rights) {}
function imap_setflag_full($imap_stream, $sequence, $flag, $options) {}
function imap_sort($imap_stream, $criteria, $reverse, $options, $search_criteria, $charset) {}
function imap_status($imap_stream, $mailbox, $options) {}
function imap_subscribe($imap_stream, $mailbox) {}
function imap_thread($imap_stream, $options) {}
function imap_timeout($timeout_type, $timeout) {}
function imap_uid($imap_stream, $msg_number) {}
function imap_undelete($imap_stream, $msg_number, $flags) {}
function imap_unsubscribe($imap_stream, $mailbox) {}
function imap_utf7_decode($text) {}
function imap_utf7_encode($data) {}
function imap_utf8($mime_encoded_text) {}
function inclued_get_data() {}
function assert_options($what, $value) {}
function assert($assertion) {}
function dl($library) {}
function extension_loaded($name) {}
function get_cfg_var($option) {}
function get_current_user() {}
function get_defined_constants($categorize) {}
function get_extension_funcs($module_name) {}
function get_include_path() {}
function get_included_files() {}
function get_loaded_extensions($zend_extensions) {}
function get_magic_quotes_gpc() {}
function get_magic_quotes_runtime() {}
function getenv($varname) {}
function getlastmod() {}
function getmygid() {}
function getmyinode() {}
function getmypid() {}
function getmyuid() {}
function getopt($options, $longopts) {}
function getrusage($who) {}
function ini_get_all($extension, $details) {}
function ini_get($varname) {}
function ini_restore($varname) {}
function ini_set($varname, $newvalue) {}
function memory_get_peak_usage($real_usage) {}
function memory_get_usage($real_usage) {}
function php_ini_loaded_file() {}
function php_ini_scanned_files() {}
function php_logo_guid() {}
function php_sapi_name() {}
function php_uname($mode) {}
function phpcredits($flag) {}
function phpinfo($what) {}
function phpversion($extension) {}
function putenv($setting) {}
function restore_include_path() {}
function set_include_path($new_include_path) {}
function set_magic_quotes_runtime($new_setting) {}
function set_time_limit($seconds) {}
function sys_get_temp_dir() {}
function version_compare($version1, $version2, $operator) {}
function zend_logo_guid() {}
function zend_thread_id() {}
function zend_version() {}
function ingres_autocommit($link) {}
function ingres_close($link) {}
function ingres_commit($link) {}
function ingres_connect($database, $username, $password, $options) {}
function ingres_cursor($link) {}
function ingres_errno($link) {}
function ingres_error($link) {}
function ingres_errsqlstate($link) {}
function ingres_fetch_array($result_type, $link) {}
function ingres_fetch_object($result_type, $link) {}
function ingres_fetch_row($link) {}
function ingres_field_length($index, $link) {}
function ingres_field_name($index, $link) {}
function ingres_field_nullable($index, $link) {}
function ingres_field_precision($index, $link) {}
function ingres_field_scale($index, $link) {}
function ingres_field_type($index, $link) {}
function ingres_num_fields($link) {}
function ingres_num_rows($link) {}
function ingres_pconnect($database, $username, $password) {}
function ingres_query($query, $link) {}
function ingres_rollback($link) {}
function grapheme_extract($haystack, $size, $extract_type, $start, $next) {}
function grapheme_stripos($haystack, $needle, $offset) {}
function grapheme_stristr($haystack, $needle, $before_needle) {}
function grapheme_strlen($input) {}
function grapheme_strpos($haystack, $needle, $offset) {}
function grapheme_strripos($haystack, $needle, $offset) {}
function grapheme_strrpos($haystack, $needle, $offset) {}
function grapheme_strstr($haystack, $needle, $before_needle) {}
function grapheme_substr($string, $start, $length) {}
function intl_error_name($error_code) {}
function intl_get_error_code() {}
function intl_get_error_message() {}
function intl_is_failure($error_code) {}
function java_last_exception_clear() {}
function java_last_exception_get() {}
function json_decode($json, $assoc) {}
function json_encode($value) {}
function kadm5_chpass_principal($handle, $principal, $password) {}
function kadm5_create_principal($handle, $principal, $password, $options) {}
function kadm5_delete_principal($handle, $principal) {}
function kadm5_destroy($handle) {}
function kadm5_flush($handle) {}
function kadm5_get_policies($handle) {}
function kadm5_get_principal($handle, $principal) {}
function kadm5_get_principals($handle) {}
function kadm5_init_with_password($admin_server, $realm, $principal, $password) {}
function kadm5_modify_principal($handle, $principal, $options) {}
function ldap_8859_to_t61($value) {}
function ldap_add($link_identifier, $dn, $entry) {}
function ldap_bind($link_identifier, $bind_rdn, $bind_password) {}
function ldap_compare($link_identifier, $dn, $attribute, $value) {}
function ldap_connect($hostname, $port) {}
function ldap_count_entries($link_identifier, $result_identifier) {}
function ldap_delete($link_identifier, $dn) {}
function ldap_dn2ufn($dn) {}
function ldap_err2str($errno) {}
function ldap_errno($link_identifier) {}
function ldap_error($link_identifier) {}
function ldap_explode_dn($dn, $with_attrib) {}
function ldap_first_attribute($link_identifier, $result_entry_identifier) {}
function ldap_first_entry($link_identifier, $result_identifier) {}
function ldap_first_reference($link, $result) {}
function ldap_free_result($result_identifier) {}
function ldap_get_attributes($link_identifier, $result_entry_identifier) {}
function ldap_get_dn($link_identifier, $result_entry_identifier) {}
function ldap_get_entries($link_identifier, $result_identifier) {}
function ldap_get_option($link_identifier, $option, $retval) {}
function ldap_get_values_len($link_identifier, $result_entry_identifier, $attribute) {}
function ldap_get_values($link_identifier, $result_entry_identifier, $attribute) {}
function ldap_list($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_mod_add($link_identifier, $dn, $entry) {}
function ldap_mod_del($link_identifier, $dn, $entry) {}
function ldap_mod_replace($link_identifier, $dn, $entry) {}
function ldap_modify($link_identifier, $dn, $entry) {}
function ldap_next_attribute($link_identifier, $result_entry_identifier) {}
function ldap_next_entry($link_identifier, $result_entry_identifier) {}
function ldap_next_reference($link, $entry) {}
function ldap_parse_reference($link, $entry, $referrals) {}
function ldap_parse_result($link, $result, $errcode, $matcheddn, $errmsg, $referrals) {}
function ldap_read($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_rename($link_identifier, $dn, $newrdn, $newparent, $deleteoldrdn) {}
function ldap_sasl_bind($link, $binddn, $password, $sasl_mech, $sasl_realm, $sasl_authz_id, $props) {}
function ldap_search($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_set_option($link_identifier, $option, $newval) {}
function ldap_set_rebind_proc($link, $callback) {}
function ldap_sort($link, $result, $sortfilter) {}
function ldap_start_tls($link) {}
function ldap_t61_to_8859($value) {}
function ldap_unbind($link_identifier) {}
function libxml_clear_errors() {}
function libxml_get_errors() {}
function libxml_get_last_error() {}
function libxml_set_streams_context($streams_context) {}
function libxml_use_internal_errors($use_errors) {}
function lzf_compress($data) {}
function lzf_decompress($data) {}
function lzf_optimized_for() {}
function ezmlm_hash($addr) {}
function mail($to, $subject, $message, $additional_headers, $additional_parameters) {}
function mailparse_determine_best_xfer_encoding($fp) {}
function mailparse_msg_create() {}
function mailparse_msg_extract_part_file($mimemail, $filename, $callbackfunc) {}
function mailparse_msg_extract_part($mimemail, $msgbody, $callbackfunc) {}
function mailparse_msg_extract_whole_part_file($mimemail, $filename, $callbackfunc) {}
function mailparse_msg_free($mimemail) {}
function mailparse_msg_get_part_data($mimemail) {}
function mailparse_msg_get_part($mimemail, $mimesection) {}
function mailparse_msg_get_structure($mimemail) {}
function mailparse_msg_parse_file($filename) {}
function mailparse_msg_parse($mimemail, $data) {}
function mailparse_rfc822_parse_addresses($addresses) {}
function mailparse_stream_encode($sourcefp, $destfp, $encoding) {}
function mailparse_uudecode_all($fp) {}
function acos($arg) {}
function abs($number) {}
function acosh($arg) {}
function asin($arg) {}
function asinh($arg) {}
function atan($arg) {}
function atan2($y, $x) {}
function atanh($arg) {}
function base_convert($number, $frombase, $tobase) {}
function bindec($binary_string) {}
function ceil($value) {}
function cos($arg) {}
function cosh($arg) {}
function decbin($number) {}
function dechex($number) {}
function decoct($number) {}
function deg2rad($number) {}
function exp($arg) {}
function expm1($arg) {}
function floor($value) {}
function fmod($x, $y) {}
function getrandmax() {}
function hexdec($hex_string) {}
function hypot($x, $y) {}
function is_finite($val) {}
function is_infinite($val) {}
function is_nan($val) {}
function lcg_value() {}
function log($arg, $base) {}
function log10($arg) {}
function log1p($number) {}
function max($values) {}
function min($values) {}
function mt_getrandmax() {}
function mt_rand() {}
function mt_srand($seed) {}
function octdec($octal_string) {}
function pi() {}
function pow($base, $exp) {}
function rad2deg($number) {}
function rand() {}
function round($val, $precision) {}
function sin($arg) {}
function sinh($arg) {}
function sqrt($arg) {}
function srand($seed) {}
function tan($arg) {}
function tanh($arg) {}
function maxdb_affected_rows($link) {}
function maxdb_autocommit($link, $mode) {}
function maxdb_change_user($link, $user, $password, $database) {}
function maxdb_character_set_name($link) {}
function maxdb_close($link) {}
function maxdb_commit($link) {}
function maxdb_connect_errno() {}
function maxdb_connect_error() {}
function maxdb_connect($host, $username, $passwd, $dbname, $port, $socket) {}
function maxdb_data_seek($result, $offset) {}
function maxdb_debug($debug) {}
function maxdb_disable_reads_from_master($link) {}
function maxdb_disable_rpl_parse($link) {}
function maxdb_dump_debug_info($link) {}
function maxdb_embedded_connect($dbname) {}
function maxdb_enable_reads_from_master($link) {}
function maxdb_enable_rpl_parse($link) {}
function maxdb_errno($link) {}
function maxdb_error($link) {}
function maxdb_fetch_array($result, $resulttype) {}
function maxdb_fetch_assoc($result) {}
function maxdb_fetch_field_direct($result, $fieldnr) {}
function maxdb_fetch_field($result) {}
function maxdb_fetch_fields($result) {}
function maxdb_fetch_lengths($result) {}
function maxdb_fetch_object($result) {}
function maxdb_fetch_row($result) {}
function maxdb_field_count($link) {}
function maxdb_field_seek($result, $fieldnr) {}
function maxdb_field_tell($result) {}
function maxdb_free_result($result) {}
function maxdb_get_client_info() {}
function maxdb_get_client_version() {}
function maxdb_get_host_info($link) {}
function maxdb_get_proto_info($link) {}
function maxdb_get_server_info($link) {}
function maxdb_get_server_version($link) {}
function maxdb_info($link) {}
function maxdb_init() {}
function maxdb_insert_id($link) {}
function maxdb_kill($link, $processid) {}
function maxdb_master_query($link, $query) {}
function maxdb_more_results($link) {}
function maxdb_multi_query($link, $query) {}
function maxdb_next_result($link) {}
function maxdb_num_fields($result) {}
function maxdb_num_rows($result) {}
function maxdb_options($link, $option, $value) {}
function maxdb_ping($link) {}
function maxdb_prepare($link, $query) {}
function maxdb_query($link, $query, $resultmode) {}
function maxdb_real_connect($link, $hostname, $username, $passwd, $dbname, $port, $socket) {}
function maxdb_real_escape_string($link, $escapestr) {}
function maxdb_real_query($link, $query) {}
function maxdb_report($flags) {}
function maxdb_rollback($link) {}
function maxdb_rpl_parse_enabled($link) {}
function maxdb_rpl_probe($link) {}
function maxdb_rpl_query_type($link) {}
function maxdb_select_db($link, $dbname) {}
function maxdb_send_query($link, $query) {}
function maxdb_server_end() {}
function maxdb_server_init($server, $groups) {}
function maxdb_sqlstate($link) {}
function maxdb_ssl_set($link, $key, $cert, $ca, $capath, $cipher) {}
function maxdb_stat($link) {}
function maxdb_stmt_affected_rows($stmt) {}
function maxdb_stmt_bind_param($stmt, $types, $var1) {}
function maxdb_stmt_bind_result($stmt, $var1) {}
function maxdb_stmt_close_long_data($stmt, $param_nr) {}
function maxdb_stmt_close($stmt) {}
function maxdb_stmt_data_seek($statement, $offset) {}
function maxdb_stmt_errno($stmt) {}
function maxdb_stmt_error($stmt) {}
function maxdb_stmt_execute($stmt) {}
function maxdb_stmt_fetch($stmt) {}
function maxdb_stmt_free_result($stmt) {}
function maxdb_stmt_init($link) {}
function maxdb_stmt_num_rows($stmt) {}
function maxdb_stmt_param_count($stmt) {}
function maxdb_stmt_prepare($stmt, $query) {}
function maxdb_stmt_reset($stmt) {}
function maxdb_stmt_result_metadata($stmt) {}
function maxdb_stmt_send_long_data($stmt, $param_nr, $data) {}
function maxdb_stmt_sqlstate($stmt) {}
function maxdb_stmt_store_result($stmt) {}
function maxdb_store_result($link) {}
function maxdb_thread_id($link) {}
function maxdb_thread_safe() {}
function maxdb_use_result($link) {}
function maxdb_warning_count($link) {}
function mb_check_encoding($var, $encoding) {}
function mb_convert_case($str, $mode, $encoding) {}
function mb_convert_encoding($str, $to_encoding, $from_encoding) {}
function mb_convert_kana($str, $option, $encoding) {}
function mb_convert_variables($to_encoding, $from_encoding, $vars) {}
function mb_decode_mimeheader($str) {}
function mb_decode_numericentity($str, $convmap, $encoding) {}
function mb_detect_encoding($str, $encoding_list, $strict) {}
function mb_detect_order($encoding_list) {}
function mb_encode_mimeheader($str, $charset, $transfer_encoding, $linefeed, $indent) {}
function mb_encode_numericentity($str, $convmap, $encoding) {}
function mb_ereg_match($pattern, $string, $option) {}
function mb_ereg_replace($pattern, $replacement, $string, $option) {}
function mb_ereg_search_getpos() {}
function mb_ereg_search_getregs() {}
function mb_ereg_search_init($string, $pattern, $option) {}
function mb_ereg_search_pos($pattern, $option) {}
function mb_ereg_search_regs($pattern, $option) {}
function mb_ereg_search_setpos($position) {}
function mb_ereg_search($pattern, $option) {}
function mb_ereg($pattern, $string, $regs) {}
function mb_eregi_replace($pattern, $replace, $string, $option) {}
function mb_eregi($pattern, $string, $regs) {}
function mb_get_info($type) {}
function mb_http_input($type) {}
function mb_http_output($encoding) {}
function mb_internal_encoding($encoding) {}
function mb_language($language) {}
function mb_list_encodings() {}
function mb_output_handler($contents, $status) {}
function mb_parse_str($encoded_string, $result) {}
function mb_preferred_mime_name($encoding) {}
function mb_regex_encoding($encoding) {}
function mb_regex_set_options($options) {}
function mb_send_mail($to, $subject, $message, $additional_headers, $additional_parameter) {}
function mb_split($pattern, $string, $limit) {}
function mb_strcut($str, $start, $length, $encoding) {}
function mb_strimwidth($str, $start, $width, $trimmarker, $encoding) {}
function mb_stripos($haystack, $needle, $offset, $encoding) {}
function mb_stristr($haystack, $needle, $part, $encoding) {}
function mb_strlen($str, $encoding) {}
function mb_strpos($haystack, $needle, $offset, $encoding) {}
function mb_strrchr($haystack, $needle, $part, $encoding) {}
function mb_strrichr($haystack, $needle, $part, $encoding) {}
function mb_strripos($haystack, $needle, $offset, $encoding) {}
function mb_strrpos($haystack, $needle, $offset, $encoding) {}
function mb_strstr($haystack, $needle, $part, $encoding) {}
function mb_strtolower($str, $encoding) {}
function mb_strtoupper($str, $encoding) {}
function mb_strwidth($str, $encoding) {}
function mb_substitute_character($substrchar) {}
function mb_substr_count($haystack, $needle, $encoding) {}
function mb_substr($str, $start, $length, $encoding) {}
function mcrypt_cbc($cipher, $key, $data, $mode, $iv) {}
function mcrypt_cfb($cipher, $key, $data, $mode, $iv) {}
function mcrypt_create_iv($size, $source) {}
function mcrypt_decrypt($cipher, $key, $data, $mode, $iv) {}
function mcrypt_ecb($cipher, $key, $data, $mode) {}
function mcrypt_enc_get_algorithms_name($td) {}
function mcrypt_enc_get_block_size($td) {}
function mcrypt_enc_get_iv_size($td) {}
function mcrypt_enc_get_key_size($td) {}
function mcrypt_enc_get_modes_name($td) {}
function mcrypt_enc_get_supported_key_sizes($td) {}
function mcrypt_enc_is_block_algorithm_mode($td) {}
function mcrypt_enc_is_block_algorithm($td) {}
function mcrypt_enc_is_block_mode($td) {}
function mcrypt_enc_self_test($td) {}
function mcrypt_encrypt($cipher, $key, $data, $mode, $iv) {}
function mcrypt_generic_deinit($td) {}
function mcrypt_generic_end($td) {}
function mcrypt_generic_init($td, $key, $iv) {}
function mcrypt_generic($td, $data) {}
function mcrypt_get_block_size($cipher) {}
function mcrypt_get_cipher_name($cipher) {}
function mcrypt_get_iv_size($cipher, $mode) {}
function mcrypt_get_key_size($cipher) {}
function mcrypt_list_algorithms($lib_dir) {}
function mcrypt_list_modes($lib_dir) {}
function mcrypt_module_close($td) {}
function mcrypt_module_get_algo_block_size($algorithm, $lib_dir) {}
function mcrypt_module_get_algo_key_size($algorithm, $lib_dir) {}
function mcrypt_module_get_supported_key_sizes($algorithm, $lib_dir) {}
function mcrypt_module_is_block_algorithm_mode($mode, $lib_dir) {}
function mcrypt_module_is_block_algorithm($algorithm, $lib_dir) {}
function mcrypt_module_is_block_mode($mode, $lib_dir) {}
function mcrypt_module_open($algorithm, $algorithm_directory, $mode, $mode_directory) {}
function mcrypt_module_self_test($algorithm, $lib_dir) {}
function mcrypt_ofb($cipher, $key, $data, $mode, $iv) {}
function mdecrypt_generic($td, $data) {}
function m_checkstatus($conn, $identifier) {}
function m_completeauthorizations($conn, $array) {}
function m_connect($conn) {}
function m_connectionerror($conn) {}
function m_deletetrans($conn, $identifier) {}
function m_destroyconn($conn) {}
function m_destroyengine() {}
function m_getcell($conn, $identifier, $column, $row) {}
function m_getcellbynum($conn, $identifier, $column, $row) {}
function m_getcommadelimited($conn, $identifier) {}
function m_getheader($conn, $identifier, $column_num) {}
function m_initconn() {}
function m_initengine($location) {}
function m_iscommadelimited($conn, $identifier) {}
function m_maxconntimeout($conn, $secs) {}
function m_monitor($conn) {}
function m_numcolumns($conn, $identifier) {}
function m_numrows($conn, $identifier) {}
function m_parsecommadelimited($conn, $identifier) {}
function m_responsekeys($conn, $identifier) {}
function m_responseparam($conn, $identifier, $key) {}
function m_returnstatus($conn, $identifier) {}
function m_setblocking($conn, $tf) {}
function m_setdropfile($conn, $directory) {}
function m_setip($conn, $host, $port) {}
function m_setssl_cafile($conn, $cafile) {}
function m_setssl_files($conn, $sslkeyfile, $sslcertfile) {}
function m_setssl($conn, $host, $port) {}
function m_settimeout($conn, $seconds) {}
function m_sslcert_gen_hash($filename) {}
function m_transactionssent($conn) {}
function m_transinqueue($conn) {}
function m_transkeyval($conn, $identifier, $key, $value) {}
function m_transnew($conn) {}
function m_transsend($conn, $identifier) {}
function m_uwait($microsecs) {}
function m_validateidentifier($conn, $tf) {}
function m_verifyconnection($conn, $tf) {}
function m_verifysslcert($conn, $tf) {}
function memcache_debug($on_off) {}
function mhash_count() {}
function mhash_get_block_size($hash) {}
function mhash_get_hash_name($hash) {}
function mhash_keygen_s2k($hash, $password, $salt, $bytes) {}
function mhash($hash, $data, $key) {}
function mime_content_type($filename) {}
function ming_keypress($char) {}
function ming_setcubicthreshold($threshold) {}
function ming_setscale($scale) {}
function ming_setswfcompression($level) {}
function ming_useconstants($use) {}
function ming_useswfversion($version) {}
function connection_aborted() {}
function connection_status() {}
function connection_timeout() {}
function constant($name) {}
function define($name, $value, $case_insensitive) {}
function defined($name) {}
function get_browser($user_agent, $return_array) {}
function ignore_user_abort($setting) {}
function pack($format, $args) {}
function php_check_syntax($filename, $error_message) {}
function php_strip_whitespace($filename) {}
function sleep($seconds) {}
function sys_getloadavg() {}
function time_nanosleep($seconds, $nanoseconds) {}
function time_sleep_until($timestamp) {}
function uniqid($prefix, $more_entropy) {}
function unpack($format, $data) {}
function usleep($micro_seconds) {}
function udm_add_search_limit($agent, $var, $val) {}
function udm_alloc_agent_array($databases) {}
function udm_alloc_agent($dbaddr, $dbmode) {}
function udm_api_version() {}
function udm_cat_list($agent, $category) {}
function udm_cat_path($agent, $category) {}
function udm_check_charset($agent, $charset) {}
function udm_check_stored($agent, $link, $doc_id) {}
function udm_clear_search_limits($agent) {}
function udm_close_stored($agent, $link) {}
function udm_crc32($agent, $str) {}
function udm_errno($agent) {}
function udm_error($agent) {}
function udm_find($agent, $query) {}
function udm_free_agent($agent) {}
function udm_free_ispell_data($agent) {}
function udm_free_res($res) {}
function udm_get_doc_count($agent) {}
function udm_get_res_field($res, $row, $field) {}
function udm_get_res_param($res, $param) {}
function udm_hash32($agent, $str) {}
function udm_load_ispell_data($agent, $var, $val1, $val2, $flag) {}
function udm_open_stored($agent, $storedaddr) {}
function udm_set_agent_param($agent, $var, $val) {}
function mqseries_back($hconn, $compCode, $reason) {}
function mqseries_begin($hconn, $beginOptions, $compCode, $reason) {}
function mqseries_close($hconn, $hobj, $compCode, $reason) {}
function mqseries_cmit($hconn, $compCode, $reason) {}
function mqseries_conn($qManagerName, $hconn, $compCode, $reason) {}
function mqseries_connx($qManagerName, $connOptions, $hconn, $compCode, $reason) {}
function mqseries_disc($hconn, $compCode, $reason) {}
function mqseries_get($hConn, $hObj, $md, $gmo, $bufferLength, $msg, $data_length, $compCode, $reason) {}
function mqseries_inq($hconn, $hobj, $selectorCount, $selectors, $intAttrCount, $intAttr, $charAttrLength, $charAttr, $compCode, $reason) {}
function mqseries_open($hconn, $objDesc, $option, $hobj, $compCode, $reason) {}
function mqseries_put($hConn, $hObj, $md, $pmo, $message, $compCode, $reason) {}
function mqseries_put1($hconn, $objDesc, $msgDesc, $pmo, $buffer, $compCode, $reason) {}
function mqseries_set($hconn, $compCode, $reason) {}
function mqseries_strerror($reason) {}
function msession_connect($host, $port) {}
function msession_count() {}
function msession_create($session, $classname, $data) {}
function msession_destroy($name) {}
function msession_disconnect() {}
function msession_find($name, $value) {}
function msession_get_array($session) {}
function msession_get_data($session) {}
function msession_get($session, $name, $value) {}
function msession_inc($session, $name) {}
function msession_list() {}
function msession_listvar($name) {}
function msession_lock($name) {}
function msession_plugin($session, $val, $param) {}
function msession_randstr($param) {}
function msession_set_array($session, $tuples) {}
function msession_set_data($session, $value) {}
function msession_set($session, $name, $value) {}
function msession_timeout($session, $param) {}
function msession_uniq($param, $classname, $data) {}
function msession_unlock($session, $key) {}
function msql_affected_rows($result) {}
function msql_close($link_identifier) {}
function msql_connect($hostname) {}
function msql_create_db($database_name, $link_identifier) {}
function msql_data_seek($result, $row_number) {}
function msql_db_query($database, $query, $link_identifier) {}
function msql_drop_db($database_name, $link_identifier) {}
function msql_error() {}
function msql_fetch_array($result, $result_type) {}
function msql_fetch_field($result, $field_offset) {}
function msql_fetch_object($result) {}
function msql_fetch_row($result) {}
function msql_field_flags($result, $field_offset) {}
function msql_field_len($result, $field_offset) {}
function msql_field_name($result, $field_offset) {}
function msql_field_seek($result, $field_offset) {}
function msql_field_table($result, $field_offset) {}
function msql_field_type($result, $field_offset) {}
function msql_free_result($result) {}
function msql_list_dbs($link_identifier) {}
function msql_list_fields($database, $tablename, $link_identifier) {}
function msql_list_tables($database, $link_identifier) {}
function msql_num_fields($result) {}
function msql_num_rows($query_identifier) {}
function msql_pconnect($hostname) {}
function msql_query($query, $link_identifier) {}
function msql_result($result, $row, $field) {}
function msql_select_db($database_name, $link_identifier) {}
function mssql_bind($stmt, $param_name, $var, $type, $is_output, $is_null, $maxlen) {}
function mssql_close($link_identifier) {}
function mssql_connect($servername, $username, $password, $new_link) {}
function mssql_data_seek($result_identifier, $row_number) {}
function mssql_execute($stmt, $skip_results) {}
function mssql_fetch_array($result, $result_type) {}
function mssql_fetch_assoc($result_id) {}
function mssql_fetch_batch($result) {}
function mssql_fetch_field($result, $field_offset) {}
function mssql_fetch_object($result) {}
function mssql_fetch_row($result) {}
function mssql_field_length($result, $offset) {}
function mssql_field_name($result, $offset) {}
function mssql_field_seek($result, $field_offset) {}
function mssql_field_type($result, $offset) {}
function mssql_free_result($result) {}
function mssql_free_statement($stmt) {}
function mssql_get_last_message() {}
function mssql_guid_string($binary, $short_format) {}
function mssql_init($sp_name, $link_identifier) {}
function mssql_min_error_severity($severity) {}
function mssql_min_message_severity($severity) {}
function mssql_next_result($result_id) {}
function mssql_num_fields($result) {}
function mssql_num_rows($result) {}
function mssql_pconnect($servername, $username, $password, $new_link) {}
function mssql_query($query, $link_identifier, $batch_size) {}
function mssql_result($result, $row, $field) {}
function mssql_rows_affected($link_identifier) {}
function mssql_select_db($database_name, $link_identifier) {}
function mysql_affected_rows($link_identifier) {}
function mysql_change_user($user, $password, $database, $link_identifier) {}
function mysql_client_encoding($link_identifier) {}
function mysql_close($link_identifier) {}
function mysql_connect($server, $username, $password, $new_link, $client_flags) {}
function mysql_create_db($database_name, $link_identifier) {}
function mysql_data_seek($result, $row_number) {}
function mysql_db_name($result, $row, $field) {}
function mysql_db_query($database, $query, $link_identifier) {}
function mysql_drop_db($database_name, $link_identifier) {}
function mysql_errno($link_identifier) {}
function mysql_error($link_identifier) {}
function mysql_escape_string($unescaped_string) {}
function mysql_fetch_array($result, $result_type) {}
function mysql_fetch_assoc($result) {}
function mysql_fetch_field($result, $field_offset) {}
function mysql_fetch_lengths($result) {}
function mysql_fetch_object($result, $class_name, $params) {}
function mysql_fetch_row($result) {}
function mysql_field_flags($result, $field_offset) {}
function mysql_field_len($result, $field_offset) {}
function mysql_field_name($result, $field_offset) {}
function mysql_field_seek($result, $field_offset) {}
function mysql_field_table($result, $field_offset) {}
function mysql_field_type($result, $field_offset) {}
function mysql_free_result($result) {}
function mysql_get_client_info() {}
function mysql_get_host_info($link_identifier) {}
function mysql_get_proto_info($link_identifier) {}
function mysql_get_server_info($link_identifier) {}
function mysql_info($link_identifier) {}
function mysql_insert_id($link_identifier) {}
function mysql_list_dbs($link_identifier) {}
function mysql_list_fields($database_name, $table_name, $link_identifier) {}
function mysql_list_processes($link_identifier) {}
function mysql_list_tables($database, $link_identifier) {}
function mysql_num_fields($result) {}
function mysql_num_rows($result) {}
function mysql_pconnect($server, $username, $password, $client_flags) {}
function mysql_ping($link_identifier) {}
function mysql_query($query, $link_identifier) {}
function mysql_real_escape_string($unescaped_string, $link_identifier) {}
function mysql_result($result, $row, $field) {}
function mysql_select_db($database_name, $link_identifier) {}
function mysql_set_charset($charset, $link_identifier) {}
function mysql_stat($link_identifier) {}
function mysql_tablename($result, $i) {}
function mysql_thread_id($link_identifier) {}
function mysql_unbuffered_query($query, $link_identifier) {}
function mysqli_disable_reads_from_master($link) {}
function mysqli_disable_rpl_parse($link) {}
function mysqli_enable_reads_from_master($link) {}
function mysqli_enable_rpl_parse($link) {}
function mysqli_master_query($link, $query) {}
function mysqli_report($flags) {}
function mysqli_rpl_parse_enabled($link) {}
function mysqli_rpl_probe($link) {}
function mysqli_rpl_query_type($link, $query) {}
function mysqli_send_query($link, $query) {}
function mysqli_slave_query($link, $query) {}
function mysqli_affected_rows($link) {}
function mysqli_connect_errno() {}
function mysqli_connect_error() {}
function mysqli_connect($host, $username, $passwd, $dbname, $port, $socket) {}
function mysqli_errno($link) {}
function mysqli_error($link) {}
function mysqli_field_count($link) {}
function mysqli_get_host_info($link) {}
function mysqli_get_proto_info($link) {}
function mysqli_get_server_info($link) {}
function mysqli_get_server_version($link) {}
function mysqli_info($link) {}
function init() {}
function mysqli_insert_id($link) {}
function prepare($query) {}
function real_query($query) {}
function mysqli_set_local_infile_default($link) {}
function mysqli_set_local_infile_handler($link, $read_func) {}
function mysqli_sqlstate($link) {}
function mysqli_stmt_init($link) {}
function store_result() {}
function mysqli_thread_id($link) {}
function mysqli_thread_safe() {}
function use_result() {}
function mysqli_warning_count($link) {}
function mysqli_field_tell($result) {}
function mysqli_num_fields($result) {}
function mysqli_fetch_lengths($result) {}
function mysqli_num_rows($result) {}
function mysqli_stmt_affected_rows($stmt) {}
function mysqli_stmt_attr_get($stmt, $attr) {}
function mysqli_stmt_attr_set($stmt, $attr, $mode) {}
function mysqli_stmt_errno($stmt) {}
function mysqli_stmt_error($stmt) {}
function mysqli_stmt_field_count($stmt) {}
function mysqli_stmt_insert_id($stmt) {}
function mysqli_stmt_num_rows($stmt) {}
function mysqli_stmt_param_count($stmt) {}
function mysqli_stmt_sqlstate($stmt) {}
function ncurses_addch($ch) {}
function ncurses_addchnstr($s, $n) {}
function ncurses_addchstr($s) {}
function ncurses_addnstr($s, $n) {}
function ncurses_addstr($text) {}
function ncurses_assume_default_colors($fg, $bg) {}
function ncurses_attroff($attributes) {}
function ncurses_attron($attributes) {}
function ncurses_attrset($attributes) {}
function ncurses_baudrate() {}
function ncurses_beep() {}
function ncurses_bkgd($attrchar) {}
function ncurses_bkgdset($attrchar) {}
function ncurses_border($left, $right, $top, $bottom, $tl_corner, $tr_corner, $bl_corner, $br_corner) {}
function ncurses_bottom_panel($panel) {}
function ncurses_can_change_color() {}
function ncurses_cbreak() {}
function ncurses_clear() {}
function ncurses_clrtobot() {}
function ncurses_clrtoeol() {}
function ncurses_color_content($color, $r, $g, $b) {}
function ncurses_color_set($pair) {}
function ncurses_curs_set($visibility) {}
function ncurses_def_prog_mode() {}
function ncurses_def_shell_mode() {}
function ncurses_define_key($definition, $keycode) {}
function ncurses_del_panel($panel) {}
function ncurses_delay_output($milliseconds) {}
function ncurses_delch() {}
function ncurses_deleteln() {}
function ncurses_delwin($window) {}
function ncurses_doupdate() {}
function ncurses_echo() {}
function ncurses_echochar($character) {}
function ncurses_end() {}
function ncurses_erase() {}
function ncurses_erasechar() {}
function ncurses_filter() {}
function ncurses_flash() {}
function ncurses_flushinp() {}
function ncurses_getch() {}
function ncurses_getmaxyx($window, $y, $x) {}
function ncurses_getmouse($mevent) {}
function ncurses_getyx($window, $y, $x) {}
function ncurses_halfdelay($tenth) {}
function ncurses_has_colors() {}
function ncurses_has_ic() {}
function ncurses_has_il() {}
function ncurses_has_key($keycode) {}
function ncurses_hide_panel($panel) {}
function ncurses_hline($charattr, $n) {}
function ncurses_inch() {}
function ncurses_init_color($color, $r, $g, $b) {}
function ncurses_init_pair($pair, $fg, $bg) {}
function ncurses_init() {}
function ncurses_insch($character) {}
function ncurses_insdelln($count) {}
function ncurses_insertln() {}
function ncurses_insstr($text) {}
function ncurses_instr($buffer) {}
function ncurses_isendwin() {}
function ncurses_keyok($keycode, $enable) {}
function ncurses_keypad($window, $bf) {}
function ncurses_killchar() {}
function ncurses_longname() {}
function ncurses_meta($window, $_8bit) {}
function ncurses_mouse_trafo($y, $x, $toscreen) {}
function ncurses_mouseinterval($milliseconds) {}
function ncurses_mousemask($newmask, $oldmask) {}
function ncurses_move_panel($panel, $startx, $starty) {}
function ncurses_move($y, $x) {}
function ncurses_mvaddch($y, $x, $c) {}
function ncurses_mvaddchnstr($y, $x, $s, $n) {}
function ncurses_mvaddchstr($y, $x, $s) {}
function ncurses_mvaddnstr($y, $x, $s, $n) {}
function ncurses_mvaddstr($y, $x, $s) {}
function ncurses_mvcur($old_y, $old_x, $new_y, $new_x) {}
function ncurses_mvdelch($y, $x) {}
function ncurses_mvgetch($y, $x) {}
function ncurses_mvhline($y, $x, $attrchar, $n) {}
function ncurses_mvinch($y, $x) {}
function ncurses_mvvline($y, $x, $attrchar, $n) {}
function ncurses_mvwaddstr($window, $y, $x, $text) {}
function ncurses_napms($milliseconds) {}
function ncurses_new_panel($window) {}
function ncurses_newpad($rows, $cols) {}
function ncurses_newwin($rows, $cols, $y, $x) {}
function ncurses_nl() {}
function ncurses_nocbreak() {}
function ncurses_noecho() {}
function ncurses_nonl() {}
function ncurses_noqiflush() {}
function ncurses_noraw() {}
function ncurses_pair_content($pair, $f, $b) {}
function ncurses_panel_above($panel) {}
function ncurses_panel_below($panel) {}
function ncurses_panel_window($panel) {}
function ncurses_pnoutrefresh($pad, $pminrow, $pmincol, $sminrow, $smincol, $smaxrow, $smaxcol) {}
function ncurses_prefresh($pad, $pminrow, $pmincol, $sminrow, $smincol, $smaxrow, $smaxcol) {}
function ncurses_putp($text) {}
function ncurses_qiflush() {}
function ncurses_raw() {}
function ncurses_refresh($ch) {}
function ncurses_replace_panel($panel, $window) {}
function ncurses_reset_prog_mode() {}
function ncurses_reset_shell_mode() {}
function ncurses_resetty() {}
function ncurses_savetty() {}
function ncurses_scr_dump($filename) {}
function ncurses_scr_init($filename) {}
function ncurses_scr_restore($filename) {}
function ncurses_scr_set($filename) {}
function ncurses_scrl($count) {}
function ncurses_show_panel($panel) {}
function ncurses_slk_attr() {}
function ncurses_slk_attroff($intarg) {}
function ncurses_slk_attron($intarg) {}
function ncurses_slk_attrset($intarg) {}
function ncurses_slk_clear() {}
function ncurses_slk_color($intarg) {}
function ncurses_slk_init($format) {}
function ncurses_slk_noutrefresh() {}
function ncurses_slk_refresh() {}
function ncurses_slk_restore() {}
function ncurses_slk_set($labelnr, $label, $format) {}
function ncurses_slk_touch() {}
function ncurses_standend() {}
function ncurses_standout() {}
function ncurses_start_color() {}
function ncurses_termattrs() {}
function ncurses_termname() {}
function ncurses_timeout($millisec) {}
function ncurses_top_panel($panel) {}
function ncurses_typeahead($fd) {}
function ncurses_ungetch($keycode) {}
function ncurses_ungetmouse($mevent) {}
function ncurses_use_env($flag) {}
function ncurses_update_panels() {}
function ncurses_use_default_colors() {}
function ncurses_use_extended_names($flag) {}
function ncurses_vidattr($intarg) {}
function ncurses_vline($charattr, $n) {}
function ncurses_waddch($window, $ch) {}
function ncurses_waddstr($window, $str, $n) {}
function ncurses_wattroff($window, $attrs) {}
function ncurses_wattron($window, $attrs) {}
function ncurses_wattrset($window, $attrs) {}
function ncurses_wborder($window, $left, $right, $top, $bottom, $tl_corner, $tr_corner, $bl_corner, $br_corner) {}
function ncurses_wclear($window) {}
function ncurses_wcolor_set($window, $color_pair) {}
function ncurses_werase($window) {}
function ncurses_wgetch($window) {}
function ncurses_whline($window, $charattr, $n) {}
function ncurses_wmouse_trafo($window, $y, $x, $toscreen) {}
function ncurses_wmove($window, $y, $x) {}
function ncurses_wnoutrefresh($window) {}
function ncurses_wrefresh($window) {}
function ncurses_wstandend($window) {}
function ncurses_wstandout($window) {}
function ncurses_wvline($window, $charattr, $n) {}
function gopher_parsedir($dirent) {}
function checkdnsrr($host, $type) {}
function closelog() {}
function define_syslog_variables() {}
function dns_get_record($hostname, $type) {}
function fsockopen($hostname, $port, $errno, $errstr, $timeout) {}
function gethostbyaddr($ip_address) {}
function gethostbyname($hostname) {}
function gethostbynamel($hostname) {}
function getmxrr($hostname, $mxhosts, $weight) {}
function getprotobyname($name) {}
function getprotobynumber($number) {}
function getservbyname($service, $protocol) {}
function getservbyport($port, $protocol) {}
function header($string, $replace, $http_response_code) {}
function headers_list() {}
function headers_sent($file, $line) {}
function inet_ntop($in_addr) {}
function inet_pton($address) {}
function ip2long($ip_address) {}
function long2ip($proper_address) {}
function openlog($ident, $option, $facility) {}
function pfsockopen($hostname, $port, $errno, $errstr, $timeout) {}
function setcookie($name, $value, $expire, $path, $domain, $secure, $httponly) {}
function setrawcookie($name, $value, $expire, $path, $domain, $secure, $httponly) {}
function syslog($priority, $message) {}
function newt_bell() {}
function newt_button_bar($buttons) {}
function newt_button($left, $top, $text) {}
function newt_centered_window($width, $height, $title) {}
function newt_checkbox_get_value($checkbox) {}
function newt_checkbox_set_flags($checkbox, $flags, $sense) {}
function newt_checkbox_set_value($checkbox, $value) {}
function newt_checkbox_tree_add_item($checkboxtree, $text, $data, $flags, $index) {}
function newt_checkbox_tree_find_item($checkboxtree, $data) {}
function newt_checkbox_tree_get_current($checkboxtree) {}
function newt_checkbox_tree_get_entry_value($checkboxtree, $data) {}
function newt_checkbox_tree_get_multi_selection($checkboxtree, $seqnum) {}
function newt_checkbox_tree_get_selection($checkboxtree) {}
function newt_checkbox_tree_multi($left, $top, $height, $seq, $flags) {}
function newt_checkbox_tree_set_current($checkboxtree, $data) {}
function newt_checkbox_tree_set_entry_value($checkboxtree, $data, $value) {}
function newt_checkbox_tree_set_entry($checkboxtree, $data, $text) {}
function newt_checkbox_tree_set_width($checkbox_tree, $width) {}
function newt_checkbox_tree($left, $top, $height, $flags) {}
function newt_checkbox($left, $top, $text, $def_value, $seq) {}
function newt_clear_key_buffer() {}
function newt_cls() {}
function newt_compact_button($left, $top, $text) {}
function newt_component_add_callback($component, $func_name, $data) {}
function newt_component_takes_focus($component, $takes_focus) {}
function newt_create_grid($cols, $rows) {}
function newt_cursor_off() {}
function newt_cursor_on() {}
function newt_delay($microseconds) {}
function newt_draw_form($form) {}
function newt_draw_root_text($left, $top, $text) {}
function newt_entry_get_value($entry) {}
function newt_entry_set_filter($entry, $filter, $data) {}
function newt_entry_set_flags($entry, $flags, $sense) {}
function newt_entry_set($entry, $value, $cursor_at_end) {}
function newt_entry($left, $top, $width, $init_value, $flags) {}
function newt_finished() {}
function newt_form_add_component($form, $component) {}
function newt_form_add_components($form, $components) {}
function newt_form_add_hot_key($form, $key) {}
function newt_form_destroy($form) {}
function newt_form_get_current($form) {}
function newt_form_run($form, $exit_struct) {}
function newt_form_set_background($from, $background) {}
function newt_form_set_height($form, $height) {}
function newt_form_set_size($form) {}
function newt_form_set_timer($form, $milliseconds) {}
function newt_form_set_width($form, $width) {}
function newt_form_watch_fd($form, $stream, $flags) {}
function newt_form($vert_bar, $help, $flags) {}
function newt_get_screen_size($cols, $rows) {}
function newt_grid_add_components_to_form($grid, $form, $recurse) {}
function newt_grid_basic_window($text, $middle, $buttons) {}
function newt_grid_free($grid, $recurse) {}
function newt_grid_get_size($grid, $width, $height) {}
function newt_grid_h_close_stacked($element1_type, $element1) {}
function newt_grid_h_stacked($element1_type, $element1) {}
function newt_grid_place($grid, $left, $top) {}
function newt_grid_set_field($grid, $col, $row, $type, $val, $pad_left, $pad_top, $pad_right, $pad_bottom, $anchor, $flags) {}
function newt_grid_simple_window($text, $middle, $buttons) {}
function newt_grid_v_close_stacked($element1_type, $element1) {}
function newt_grid_v_stacked($element1_type, $element1) {}
function newt_grid_wrapped_window_at($grid, $title, $left, $top) {}
function newt_grid_wrapped_window($grid, $title) {}
function newt_init() {}
function newt_label_set_text($label, $text) {}
function newt_label($left, $top, $text) {}
function newt_listbox_append_entry($listbox, $text, $data) {}
function newt_listbox_clear_selection($listbox) {}
function newt_listbox_clear($listobx) {}
function newt_listbox_delete_entry($listbox, $key) {}
function newt_listbox_get_current($listbox) {}
function newt_listbox_get_selection($listbox) {}
function newt_listbox_insert_entry($listbox, $text, $data, $key) {}
function newt_listbox_item_count($listbox) {}
function newt_listbox_select_item($listbox, $key, $sense) {}
function newt_listbox_set_current_by_key($listbox, $key) {}
function newt_listbox_set_current($listbox, $num) {}
function newt_listbox_set_data($listbox, $num, $data) {}
function newt_listbox_set_entry($listbox, $num, $text) {}
function newt_listbox_set_width($listbox, $width) {}
function newt_listbox($left, $top, $height, $flags) {}
function newt_listitem_get_data($item) {}
function newt_listitem_set($item, $text) {}
function newt_listitem($left, $top, $text, $is_default, $prev_item, $data, $flags) {}
function newt_open_window($left, $top, $width, $height, $title) {}
function newt_pop_help_line() {}
function newt_pop_window() {}
function newt_push_help_line($text) {}
function newt_radio_get_current($set_member) {}
function newt_radiobutton($left, $top, $text, $is_default, $prev_button) {}
function newt_redraw_help_line() {}
function newt_reflow_text($text, $width, $flex_down, $flex_up, $actual_width, $actual_height) {}
function newt_refresh() {}
function newt_resize_screen($redraw) {}
function newt_resume() {}
function newt_run_form($form) {}
function newt_scale_set($scale, $amount) {}
function newt_scale($left, $top, $width, $full_value) {}
function newt_scrollbar_set($scrollbar, $where, $total) {}
function newt_set_help_callback($function) {}
function newt_set_suspend_callback($function, $data) {}
function newt_suspend() {}
function newt_textbox_get_num_lines($textbox) {}
function newt_textbox_reflowed($left, $top, $text, $width, $flex_down, $flex_up, $flags) {}
function newt_textbox_set_height($textbox, $height) {}
function newt_textbox_set_text($textbox, $text) {}
function newt_textbox($left, $top, $width, $height, $flags) {}
function newt_vertical_scrollbar($left, $top, $height, $normal_colorset, $thumb_colorset) {}
function newt_wait_for_key() {}
function newt_win_choice($title, $button1_text, $button2_text, $format, $args) {}
function newt_win_entries($title, $text, $suggested_width, $flex_down, $flex_up, $data_width, $items, $button1) {}
function newt_win_menu($title, $text, $suggestedWidth, $flexDown, $flexUp, $maxListHeight, $items, $listItem, $button1) {}
function newt_win_message($title, $button_text, $format, $args) {}
function newt_win_messagev($title, $button_text, $format, $args) {}
function newt_win_ternary($title, $button1_text, $button2_text, $button3_text, $format, $args) {}
function yp_all($domain, $map, $callback) {}
function yp_cat($domain, $map) {}
function yp_err_string($errorcode) {}
function yp_errno() {}
function yp_first($domain, $map) {}
function yp_get_default_domain() {}
function yp_master($domain, $map) {}
function yp_match($domain, $map, $key) {}
function yp_next($domain, $map, $key) {}
function yp_order($domain, $map) {}
function notes_body($server, $mailbox, $msg_number) {}
function notes_copy_db($from_database_name, $to_database_name) {}
function notes_create_db($database_name) {}
function notes_create_note($database_name, $form_name) {}
function notes_drop_db($database_name) {}
function notes_find_note($database_name, $name, $type) {}
function notes_header_info($server, $mailbox, $msg_number) {}
function notes_list_msgs($db) {}
function notes_mark_read($database_name, $user_name, $note_id) {}
function notes_mark_unread($database_name, $user_name, $note_id) {}
function notes_nav_create($database_name, $name) {}
function notes_search($database_name, $keywords) {}
function notes_unread($database_name, $user_name) {}
function notes_version($database_name) {}
function nsapi_request_headers() {}
function nsapi_response_headers() {}
function nsapi_virtual($uri) {}
function aggregate_info($object) {}
function aggregate_methods_by_list($object, $class_name, $methods_list, $exclude) {}
function aggregate_methods_by_regexp($object, $class_name, $regexp, $exclude) {}
function aggregate_methods($object, $class_name) {}
function aggregate_properties_by_list($object, $class_name, $properties_list, $exclude) {}
function aggregate_properties_by_regexp($object, $class_name, $regexp, $exclude) {}
function aggregate_properties($object, $class_name) {}
function aggregate($object, $class_name) {}
function deaggregate($object, $class_name) {}
function oci_bind_array_by_name($statement, $name, $var_array, $max_table_length, $max_item_length, $type) {}
function oci_bind_by_name($statement, $ph_name, $variable, $maxlength, $type) {}
function oci_cancel($statement) {}
function oci_close($connection) {}
function oci_commit($connection) {}
function oci_connect($username, $password, $db, $charset, $session_mode) {}
function oci_define_by_name($statement, $column_name, $variable, $type) {}
function oci_error($source) {}
function oci_execute($statement, $mode) {}
function oci_fetch_all($statement, $output, $skip, $maxrows, $flags) {}
function oci_fetch_array($statement, $mode) {}
function oci_fetch_assoc($statement) {}
function oci_fetch_object($statement) {}
function oci_fetch_row($statement) {}
function oci_fetch($statement) {}
function oci_field_is_null($statement, $field) {}
function oci_field_name($statement, $field) {}
function oci_field_precision($statement, $field) {}
function oci_field_scale($statement, $field) {}
function oci_field_size($statement, $field) {}
function oci_field_type_raw($statement, $field) {}
function oci_field_type($statement, $field) {}
function oci_free_statement($statement) {}
function oci_internal_debug($onoff) {}
function oci_lob_copy($lob_to, $lob_from, $length) {}
function oci_lob_is_equal($lob1, $lob2) {}
function oci_new_collection($connection, $tdo, $schema) {}
function oci_new_connect($username, $password, $db, $charset, $session_mode) {}
function oci_new_cursor($connection) {}
function oci_new_descriptor($connection, $type) {}
function oci_num_fields($statement) {}
function oci_num_rows($statement) {}
function oci_parse($connection, $query) {}
function oci_password_change($connection, $username, $old_password, $new_password) {}
function oci_pconnect($username, $password, $db, $charset, $session_mode) {}
function oci_result($statement, $field) {}
function oci_rollback($connection) {}
function oci_server_version($connection) {}
function oci_set_prefetch($statement, $rows) {}
function oci_statement_type($statement) {}
function ocifetchinto($statement, $result, $mode) {}
function openal_buffer_create() {}
function openal_buffer_data($buffer, $format, $data, $freq) {}
function openal_buffer_destroy($buffer) {}
function openal_buffer_get($buffer, $property) {}
function openal_buffer_loadwav($buffer, $wavfile) {}
function openal_context_create($device) {}
function openal_context_current($context) {}
function openal_context_destroy($context) {}
function openal_context_process($context) {}
function openal_context_suspend($context) {}
function openal_device_close($device) {}
function openal_device_open($device_desc) {}
function openal_listener_get($property) {}
function openal_listener_set($property, $setting) {}
function openal_source_create() {}
function openal_source_destroy($source) {}
function openal_source_get($source, $property) {}
function openal_source_pause($source) {}
function openal_source_play($source) {}
function openal_source_rewind($source) {}
function openal_source_set($source, $property, $setting) {}
function openal_source_stop($source) {}
function openal_stream($source, $format, $rate) {}
function openssl_csr_export_to_file($csr, $outfilename, $notext) {}
function openssl_csr_export($csr, $out, $notext) {}
function openssl_csr_get_public_key($csr, $use_shortnames) {}
function openssl_csr_get_subject($csr, $use_shortnames) {}
function openssl_csr_new($dn, $privkey, $configargs, $extraattribs) {}
function openssl_csr_sign($csr, $cacert, $priv_key, $days, $configargs, $serial) {}
function openssl_error_string() {}
function openssl_free_key($key_identifier) {}
function openssl_open($sealed_data, $open_data, $env_key, $priv_key_id) {}
function openssl_pkcs12_export_to_file($x509, $filename, $priv_key, $pass, $args) {}
function openssl_pkcs12_export($x509, $out, $priv_key, $pass, $args) {}
function openssl_pkcs12_read($PKCS12, $certs, $pass) {}
function openssl_pkcs7_decrypt($infilename, $outfilename, $recipcert, $recipkey) {}
function openssl_pkcs7_encrypt($infile, $outfile, $recipcerts, $headers, $flags, $cipherid) {}
function openssl_pkcs7_sign($infilename, $outfilename, $signcert, $privkey, $headers, $flags, $extracerts) {}
function openssl_pkcs7_verify($filename, $flags, $outfilename, $cainfo, $extracerts, $content) {}
function openssl_pkey_export_to_file($key, $outfilename, $passphrase, $configargs) {}
function openssl_pkey_export($key, $out, $passphrase, $configargs) {}
function openssl_pkey_free($key) {}
function openssl_pkey_get_details($key) {}
function openssl_pkey_get_private($key, $passphrase) {}
function openssl_pkey_get_public($certificate) {}
function openssl_pkey_new($configargs) {}
function openssl_private_decrypt($data, $decrypted, $key, $padding) {}
function openssl_private_encrypt($data, $crypted, $key, $padding) {}
function openssl_public_decrypt($data, $decrypted, $key, $padding) {}
function openssl_public_encrypt($data, $crypted, $key, $padding) {}
function openssl_seal($data, $sealed_data, $env_keys, $pub_key_ids) {}
function openssl_sign($data, $signature, $priv_key_id, $signature_alg) {}
function openssl_verify($data, $signature, $pub_key_id, $signature_alg) {}
function openssl_x509_check_private_key($cert, $key) {}
function openssl_x509_checkpurpose($x509cert, $purpose, $cainfo, $untrustedfile) {}
function openssl_x509_export_to_file($x509, $outfilename, $notext) {}
function openssl_x509_export($x509, $output, $notext) {}
function openssl_x509_free($x509cert) {}
function openssl_x509_parse($x509cert, $shortnames) {}
function openssl_x509_read($x509certdata) {}
function flush() {}
function ob_clean() {}
function ob_end_clean() {}
function ob_end_flush() {}
function ob_flush() {}
function ob_get_clean() {}
function ob_get_contents() {}
function ob_get_flush() {}
function ob_get_length() {}
function ob_get_level() {}
function ob_get_status($full_status) {}
function ob_gzhandler($buffer, $mode) {}
function ob_implicit_flush($flag) {}
function ob_list_handlers() {}
function ob_start($output_callback, $chunk_size, $erase) {}
function output_add_rewrite_var($name, $value) {}
function output_reset_rewrite_vars() {}
function overload($class_name) {}
function ovrimos_close($connection) {}
function ovrimos_commit($connection_id) {}
function ovrimos_connect($host, $dborport, $user, $password) {}
function ovrimos_cursor($result_id) {}
function ovrimos_exec($connection_id, $query) {}
function ovrimos_execute($result_id, $parameters_array) {}
function ovrimos_fetch_into($result_id, $result_array, $how, $rownumber) {}
function ovrimos_fetch_row($result_id, $how, $row_number) {}
function ovrimos_field_len($result_id, $field_number) {}
function ovrimos_field_name($result_id, $field_number) {}
function ovrimos_field_num($result_id, $field_name) {}
function ovrimos_field_type($result_id, $field_number) {}
function ovrimos_free_result($result_id) {}
function ovrimos_longreadlen($result_id, $length) {}
function ovrimos_num_fields($result_id) {}
function ovrimos_num_rows($result_id) {}
function ovrimos_prepare($connection_id, $query) {}
function ovrimos_result_all($result_id, $format) {}
function ovrimos_result($result_id, $field) {}
function ovrimos_rollback($connection_id) {}
function px_close($pxdoc) {}
function px_create_fp($pxdoc, $file, $fielddesc) {}
function px_date2string($pxdoc, $value, $format) {}
function px_delete_record($pxdoc, $num) {}
function px_delete($pxdoc) {}
function px_get_field($pxdoc, $fieldno) {}
function px_get_info($pxdoc) {}
function px_get_parameter($pxdoc, $name) {}
function px_get_record($pxdoc, $num, $mode) {}
function px_get_schema($pxdoc, $mode) {}
function px_get_value($pxdoc, $name) {}
function px_insert_record($pxdoc, $data) {}
function px_new() {}
function px_numfields($pxdoc) {}
function px_numrecords($pxdoc) {}
function px_open_fp($pxdoc, $file) {}
function px_put_record($pxdoc, $record, $recpos) {}
function px_retrieve_record($pxdoc, $num, $mode) {}
function px_set_blob_file($pxdoc, $filename) {}
function px_set_parameter($pxdoc, $name, $value) {}
function px_set_tablename($pxdoc, $name) {}
function px_set_targetencoding($pxdoc, $encoding) {}
function px_set_value($pxdoc, $name, $value) {}
function px_timestamp2string($pxdoc, $value, $format) {}
function px_update_record($pxdoc, $data, $num) {}
function parsekit_compile_file($filename, $errors, $options) {}
function parsekit_compile_string($phpcode, $errors, $options) {}
function parsekit_func_arginfo($function) {}
function pcntl_alarm($seconds) {}
function pcntl_exec($path, $args, $envs) {}
function pcntl_fork() {}
function pcntl_getpriority($pid, $process_identifier) {}
function pcntl_setpriority($priority, $pid, $process_identifier) {}
function pcntl_signal($signo, $handler, $restart_syscalls) {}
function pcntl_wait($status, $options) {}
function pcntl_waitpid($pid, $status, $options) {}
function pcntl_wexitstatus($status) {}
function pcntl_wifexited($status) {}
function pcntl_wifsignaled($status) {}
function pcntl_wifstopped($status) {}
function pcntl_wstopsig($status) {}
function pcntl_wtermsig($status) {}
function preg_grep($pattern, $input, $flags) {}
function preg_last_error() {}
function preg_match_all($pattern, $subject, $matches, $flags, $offset) {}
function preg_match($pattern, $subject, $matches, $flags, $offset) {}
function preg_quote($str, $delimiter) {}
function preg_replace_callback($pattern, $callback, $subject, $limit, $count) {}
function preg_replace($pattern, $replacement, $subject, $limit, $count) {}
function preg_split($pattern, $subject, $limit, $flags) {}
function PDF_activate_item($pdfdoc, $id) {}
function PDF_add_launchlink($pdfdoc, $llx, $lly, $urx, $ury, $filename) {}
function PDF_add_locallink($pdfdoc, $lowerleftx, $lowerlefty, $upperrightx, $upperrighty, $page, $dest) {}
function PDF_add_nameddest($pdfdoc, $name, $optlist) {}
function PDF_add_note($pdfdoc, $llx, $lly, $urx, $ury, $contents, $title, $icon, $open) {}
function PDF_add_pdflink($pdfdoc, $bottom_left_x, $bottom_left_y, $up_right_x, $up_right_y, $filename, $page, $dest) {}
function PDF_add_table_cell($pdfdoc, $table, $column, $row, $text, $optlist) {}
function PDF_add_textflow($pdfdoc, $textflow, $text, $optlist) {}
function PDF_add_thumbnail($pdfdoc, $image) {}
function PDF_add_weblink($pdfdoc, $lowerleftx, $lowerlefty, $upperrightx, $upperrighty, $url) {}
function PDF_arc($p, $x, $y, $r, $alpha, $beta) {}
function PDF_arcn($p, $x, $y, $r, $alpha, $beta) {}
function PDF_attach_file($pdfdoc, $llx, $lly, $urx, $ury, $filename, $description, $author, $mimetype, $icon) {}
function PDF_begin_document($pdfdoc, $filename, $optlist) {}
function PDF_begin_font($pdfdoc, $filename, $a, $b, $c, $d, $e, $f, $optlist) {}
function PDF_begin_glyph($pdfdoc, $glyphname, $wx, $llx, $lly, $urx, $ury) {}
function PDF_begin_item($pdfdoc, $tag, $optlist) {}
function PDF_begin_layer($pdfdoc, $layer) {}
function PDF_begin_page_ext($pdfdoc, $width, $height, $optlist) {}
function PDF_begin_page($pdfdoc, $width, $height) {}
function PDF_begin_pattern($pdfdoc, $width, $height, $xstep, $ystep, $painttype) {}
function PDF_begin_template_ext($pdfdoc, $width, $height, $optlist) {}
function PDF_begin_template($pdfdoc, $width, $height) {}
function PDF_circle($pdfdoc, $x, $y, $r) {}
function PDF_clip($p) {}
function PDF_close_image($p, $image) {}
function PDF_close_pdi_page($p, $page) {}
function PDF_close_pdi($p, $doc) {}
function PDF_close($p) {}
function PDF_closepath_fill_stroke($p) {}
function PDF_closepath_stroke($p) {}
function PDF_closepath($p) {}
function PDF_concat($p, $a, $b, $c, $d, $e, $f) {}
function PDF_continue_text($p, $text) {}
function PDF_create_3dview($pdfdoc, $username, $optlist) {}
function PDF_create_action($pdfdoc, $type, $optlist) {}
function PDF_create_annotation($pdfdoc, $llx, $lly, $urx, $ury, $type, $optlist) {}
function PDF_create_bookmark($pdfdoc, $text, $optlist) {}
function PDF_create_field($pdfdoc, $llx, $lly, $urx, $ury, $name, $type, $optlist) {}
function PDF_create_fieldgroup($pdfdoc, $name, $optlist) {}
function PDF_create_gstate($pdfdoc, $optlist) {}
function PDF_create_pvf($pdfdoc, $filename, $data, $optlist) {}
function PDF_create_textflow($pdfdoc, $text, $optlist) {}
function PDF_curveto($p, $x1, $y1, $x2, $y2, $x3, $y3) {}
function PDF_define_layer($pdfdoc, $name, $optlist) {}
function PDF_delete_pvf($pdfdoc, $filename) {}
function PDF_delete_table($pdfdoc, $table, $optlist) {}
function PDF_delete_textflow($pdfdoc, $textflow) {}
function PDF_delete($pdfdoc) {}
function PDF_encoding_set_char($pdfdoc, $encoding, $slot, $glyphname, $uv) {}
function PDF_end_document($pdfdoc, $optlist) {}
function PDF_end_font($pdfdoc) {}
function PDF_end_glyph($pdfdoc) {}
function PDF_end_item($pdfdoc, $id) {}
function PDF_end_layer($pdfdoc) {}
function PDF_end_page_ext($pdfdoc, $optlist) {}
function PDF_end_page($p) {}
function PDF_end_pattern($p) {}
function PDF_end_template($p) {}
function PDF_endpath($p) {}
function PDF_fill_imageblock($pdfdoc, $page, $blockname, $image, $optlist) {}
function PDF_fill_pdfblock($pdfdoc, $page, $blockname, $contents, $optlist) {}
function PDF_fill_stroke($p) {}
function PDF_fill_textblock($pdfdoc, $page, $blockname, $text, $optlist) {}
function PDF_fill($p) {}
function PDF_findfont($p, $fontname, $encoding, $embed) {}
function PDF_fit_image($pdfdoc, $image, $x, $y, $optlist) {}
function PDF_fit_pdi_page($pdfdoc, $page, $x, $y, $optlist) {}
function PDF_fit_table($pdfdoc, $table, $llx, $lly, $urx, $ury, $optlist) {}
function PDF_fit_textflow($pdfdoc, $textflow, $llx, $lly, $urx, $ury, $optlist) {}
function PDF_fit_textline($pdfdoc, $text, $x, $y, $optlist) {}
function PDF_get_apiname($pdfdoc) {}
function PDF_get_buffer($p) {}
function PDF_get_errmsg($pdfdoc) {}
function PDF_get_errnum($pdfdoc) {}
function PDF_get_majorversion() {}
function PDF_get_minorversion() {}
function PDF_get_parameter($p, $key, $modifier) {}
function PDF_get_pdi_parameter($p, $key, $doc, $page, $reserved) {}
function PDF_get_pdi_value($p, $key, $doc, $page, $reserved) {}
function PDF_get_value($p, $key, $modifier) {}
function PDF_info_matchbox($pdfdoc, $boxname, $num, $keyword) {}
function PDF_info_table($pdfdoc, $table, $keyword) {}
function PDF_info_textflow($pdfdoc, $textflow, $keyword) {}
function PDF_info_textline($pdfdoc, $text, $keyword, $optlist) {}
function PDF_initgraphics($p) {}
function PDF_lineto($p, $x, $y) {}
function PDF_load_3ddata($pdfdoc, $filename, $optlist) {}
function PDF_load_font($pdfdoc, $fontname, $encoding, $optlist) {}
function PDF_load_iccprofile($pdfdoc, $profilename, $optlist) {}
function PDF_load_image($pdfdoc, $imagetype, $filename, $optlist) {}
function PDF_makespotcolor($p, $spotname) {}
function PDF_moveto($p, $x, $y) {}
function PDF_new() {}
function PDF_open_ccitt($pdfdoc, $filename, $width, $height, $BitReverse, $k, $Blackls1) {}
function PDF_open_file($p, $filename) {}
function PDF_open_image_file($p, $imagetype, $filename, $stringparam, $intparam) {}
function PDF_open_image($p, $imagetype, $source, $data, $length, $width, $height, $components, $bpc, $params) {}
function PDF_open_memory_image($p, $image) {}
function PDF_open_pdi_page($p, $doc, $pagenumber, $optlist) {}
function PDF_open_pdi($pdfdoc, $filename, $optlist, $len) {}
function PDF_pcos_get_number($p, $doc, $path) {}
function PDF_pcos_get_stream($p, $doc, $optlist, $path) {}
function PDF_pcos_get_string($p, $doc, $path) {}
function PDF_place_image($pdfdoc, $image, $x, $y, $scale) {}
function PDF_place_pdi_page($pdfdoc, $page, $x, $y, $sx, $sy) {}
function PDF_process_pdi($pdfdoc, $doc, $page, $optlist) {}
function PDF_rect($p, $x, $y, $width, $height) {}
function PDF_restore($p) {}
function PDF_resume_page($pdfdoc, $optlist) {}
function PDF_rotate($p, $phi) {}
function PDF_save($p) {}
function PDF_scale($p, $sx, $sy) {}
function PDF_set_border_color($p, $red, $green, $blue) {}
function PDF_set_border_dash($pdfdoc, $black, $white) {}
function PDF_set_border_style($pdfdoc, $style, $width) {}
function PDF_set_gstate($pdfdoc, $gstate) {}
function PDF_set_info($p, $key, $value) {}
function PDF_set_layer_dependency($pdfdoc, $type, $optlist) {}
function PDF_set_parameter($p, $key, $value) {}
function PDF_set_text_pos($p, $x, $y) {}
function PDF_set_value($p, $key, $value) {}
function PDF_setcolor($p, $fstype, $colorspace, $c1, $c2, $c3, $c4) {}
function PDF_setdash($pdfdoc, $b, $w) {}
function PDF_setdashpattern($pdfdoc, $optlist) {}
function PDF_setflat($pdfdoc, $flatness) {}
function PDF_setfont($pdfdoc, $font, $fontsize) {}
function PDF_setgray_fill($p, $g) {}
function PDF_setgray_stroke($p, $g) {}
function PDF_setgray($p, $g) {}
function PDF_setlinecap($p, $linecap) {}
function PDF_setlinejoin($p, $value) {}
function PDF_setlinewidth($p, $width) {}
function PDF_setmatrix($p, $a, $b, $c, $d, $e, $f) {}
function PDF_setmiterlimit($pdfdoc, $miter) {}
function PDF_setrgbcolor_fill($p, $red, $green, $blue) {}
function PDF_setrgbcolor_stroke($p, $red, $green, $blue) {}
function PDF_setrgbcolor($p, $red, $green, $blue) {}
function PDF_shading_pattern($pdfdoc, $shading, $optlist) {}
function PDF_shading($pdfdoc, $shtype, $x0, $y0, $x1, $y1, $c1, $c2, $c3, $c4, $optlist) {}
function PDF_shfill($pdfdoc, $shading) {}
function PDF_show_boxed($p, $text, $left, $top, $width, $height, $mode, $feature) {}
function PDF_show_xy($p, $text, $x, $y) {}
function PDF_show($pdfdoc, $text) {}
function PDF_skew($p, $alpha, $beta) {}
function PDF_stringwidth($p, $text, $font, $fontsize) {}
function PDF_stroke($p) {}
function PDF_suspend_page($pdfdoc, $optlist) {}
function PDF_translate($p, $tx, $ty) {}
function PDF_utf16_to_utf8($pdfdoc, $utf16string) {}
function PDF_utf32_to_utf16($pdfdoc, $utf32string, $ordering) {}
function PDF_utf8_to_utf16($pdfdoc, $utf8string, $ordering) {}
function pg_affected_rows($result) {}
function pg_cancel_query($connection) {}
function pg_client_encoding($connection) {}
function pg_close($connection) {}
function pg_connect($connection_string, $connect_type) {}
function pg_connection_busy($connection) {}
function pg_connection_reset($connection) {}
function pg_connection_status($connection) {}
function pg_convert($connection, $table_name, $assoc_array, $options) {}
function pg_copy_from($connection, $table_name, $rows, $delimiter, $null_as) {}
function pg_copy_to($connection, $table_name, $delimiter, $null_as) {}
function pg_dbname($connection) {}
function pg_delete($connection, $table_name, $assoc_array, $options) {}
function pg_end_copy($connection) {}
function pg_escape_bytea($connection, $data) {}
function pg_escape_string($connection, $data) {}
function pg_execute($connection, $stmtname, $params) {}
function pg_fetch_all_columns($result, $column) {}
function pg_fetch_all($result) {}
function pg_fetch_array($result, $row, $result_type) {}
function pg_fetch_assoc($result, $row) {}
function pg_fetch_object($result, $row, $result_type) {}
function pg_fetch_result($result, $row, $field) {}
function pg_fetch_row($result, $row) {}
function pg_field_is_null($result, $row, $field) {}
function pg_field_name($result, $field_number) {}
function pg_field_num($result, $field_name) {}
function pg_field_prtlen($result, $row_number, $field_name_or_number) {}
function pg_field_size($result, $field_number) {}
function pg_field_table($result, $field_number, $oid_only) {}
function pg_field_type_oid($result, $field_number) {}
function pg_field_type($result, $field_number) {}
function pg_free_result($result) {}
function pg_get_notify($connection, $result_type) {}
function pg_get_pid($connection) {}
function pg_get_result($connection) {}
function pg_host($connection) {}
function pg_insert($connection, $table_name, $assoc_array, $options) {}
function pg_last_error($connection) {}
function pg_last_notice($connection) {}
function pg_last_oid($result) {}
function pg_lo_close($large_object) {}
function pg_lo_create($connection, $object_id) {}
function pg_lo_export($connection, $oid, $pathname) {}
function pg_lo_import($connection, $pathname, $object_id) {}
function pg_lo_open($connection, $oid, $mode) {}
function pg_lo_read_all($large_object) {}
function pg_lo_read($large_object, $len) {}
function pg_lo_seek($large_object, $offset, $whence) {}
function pg_lo_tell($large_object) {}
function pg_lo_unlink($connection, $oid) {}
function pg_lo_write($large_object, $data, $len) {}
function pg_meta_data($connection, $table_name) {}
function pg_num_fields($result) {}
function pg_num_rows($result) {}
function pg_options($connection) {}
function pg_parameter_status($connection, $param_name) {}
function pg_pconnect($connection_string, $connect_type) {}
function pg_ping($connection) {}
function pg_port($connection) {}
function pg_prepare($connection, $stmtname, $query) {}
function pg_put_line($data) {}
function pg_query_params($connection, $query, $params) {}
function pg_query($query) {}
function pg_result_error_field($result, $fieldcode) {}
function pg_result_error($result) {}
function pg_result_seek($result, $offset) {}
function pg_result_status($result, $type) {}
function pg_select($connection, $table_name, $assoc_array, $options) {}
function pg_send_execute($connection, $stmtname, $params) {}
function pg_send_prepare($connection, $stmtname, $query) {}
function pg_send_query_params($connection, $query, $params) {}
function pg_send_query($connection, $query) {}
function pg_set_client_encoding($encoding) {}
function pg_set_error_verbosity($connection, $verbosity) {}
function pg_trace($pathname, $mode, $connection) {}
function pg_transaction_status($connection) {}
function pg_tty($connection) {}
function pg_unescape_bytea($data) {}
function pg_untrace($connection) {}
function pg_update($connection, $table_name, $data, $condition, $options) {}
function pg_version($connection) {}
function posix_access($file, $mode) {}
function posix_ctermid() {}
function posix_get_last_error() {}
function posix_getcwd() {}
function posix_getegid() {}
function posix_geteuid() {}
function posix_getgid() {}
function posix_getgrgid($gid) {}
function posix_getgrnam($name) {}
function posix_getgroups() {}
function posix_getlogin() {}
function posix_getpgid($pid) {}
function posix_getpgrp() {}
function posix_getpid() {}
function posix_getppid() {}
function posix_getpwnam($username) {}
function posix_getpwuid($uid) {}
function posix_getrlimit() {}
function posix_getsid($pid) {}
function posix_getuid() {}
function posix_initgroups($name, $base_group_id) {}
function posix_isatty($fd) {}
function posix_kill($pid, $sig) {}
function posix_mkfifo($pathname, $mode) {}
function posix_mknod($pathname, $mode, $major, $minor) {}
function posix_setegid($gid) {}
function posix_seteuid($uid) {}
function posix_setgid($gid) {}
function posix_setpgid($pid, $pgid) {}
function posix_setsid() {}
function posix_setuid($uid) {}
function posix_strerror($errno) {}
function posix_times() {}
function posix_ttyname($fd) {}
function posix_uname() {}
function printer_abort($printer_handle) {}
function printer_close($printer_handle) {}
function printer_create_brush($style, $color) {}
function printer_create_dc($printer_handle) {}
function printer_create_font($face, $height, $width, $font_weight, $italic, $underline, $strikeout, $orientation) {}
function printer_create_pen($style, $width, $color) {}
function printer_delete_brush($brush_handle) {}
function printer_delete_dc($printer_handle) {}
function printer_delete_font($font_handle) {}
function printer_delete_pen($pen_handle) {}
function printer_draw_bmp($printer_handle, $filename, $x, $y, $width, $height) {}
function printer_draw_chord($printer_handle, $rec_x, $rec_y, $rec_x1, $rec_y1, $rad_x, $rad_y, $rad_x1, $rad_y1) {}
function printer_draw_elipse($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y) {}
function printer_draw_line($printer_handle, $from_x, $from_y, $to_x, $to_y) {}
function printer_draw_pie($printer_handle, $rec_x, $rec_y, $rec_x1, $rec_y1, $rad1_x, $rad1_y, $rad2_x, $rad2_y) {}
function printer_draw_rectangle($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y) {}
function printer_draw_roundrect($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y, $width, $height) {}
function printer_draw_text($printer_handle, $text, $x, $y) {}
function printer_end_doc($printer_handle) {}
function printer_end_page($printer_handle) {}
function printer_get_option($printer_handle, $option) {}
function printer_list($enumtype, $name, $level) {}
function printer_logical_fontheight($printer_handle, $height) {}
function printer_open($printername) {}
function printer_select_brush($printer_handle, $brush_handle) {}
function printer_select_font($printer_handle, $font_handle) {}
function printer_select_pen($printer_handle, $pen_handle) {}
function printer_set_option($printer_handle, $option, $value) {}
function printer_start_doc($printer_handle, $document) {}
function printer_start_page($printer_handle) {}
function printer_write($printer_handle, $content) {}
function ps_add_bookmark($psdoc, $text, $parent, $open) {}
function ps_add_launchlink($psdoc, $llx, $lly, $urx, $ury, $filename) {}
function ps_add_locallink($psdoc, $llx, $lly, $urx, $ury, $page, $dest) {}
function ps_add_note($psdoc, $llx, $lly, $urx, $ury, $contents, $title, $icon, $open) {}
function ps_add_pdflink($psdoc, $llx, $lly, $urx, $ury, $filename, $page, $dest) {}
function ps_add_weblink($psdoc, $llx, $lly, $urx, $ury, $url) {}
function ps_arc($psdoc, $x, $y, $radius, $alpha, $beta) {}
function ps_arcn($psdoc, $x, $y, $radius, $alpha, $beta) {}
function ps_begin_page($psdoc, $width, $height) {}
function ps_begin_pattern($psdoc, $width, $height, $xstep, $ystep, $painttype) {}
function ps_begin_template($psdoc, $width, $height) {}
function ps_circle($psdoc, $x, $y, $radius) {}
function ps_clip($psdoc) {}
function ps_close_image($psdoc, $imageid) {}
function ps_close($psdoc) {}
function ps_closepath_stroke($psdoc) {}
function ps_closepath($psdoc) {}
function ps_continue_text($psdoc, $text) {}
function ps_curveto($psdoc, $x1, $y1, $x2, $y2, $x3, $y3) {}
function ps_delete($psdoc) {}
function ps_end_page($psdoc) {}
function ps_end_pattern($psdoc) {}
function ps_end_template($psdoc) {}
function ps_fill_stroke($psdoc) {}
function ps_fill($psdoc) {}
function ps_findfont($psdoc, $fontname, $encoding, $embed) {}
function ps_get_buffer($psdoc) {}
function ps_get_parameter($psdoc, $name, $modifier) {}
function ps_get_value($psdoc, $name, $modifier) {}
function ps_hyphenate($psdoc, $text) {}
function ps_include_file($psdoc, $file) {}
function ps_lineto($psdoc, $x, $y) {}
function ps_makespotcolor($psdoc, $name, $reserved) {}
function ps_moveto($psdoc, $x, $y) {}
function ps_new() {}
function ps_open_file($psdoc, $filename) {}
function ps_open_image_file($psdoc, $type, $filename, $stringparam, $intparam) {}
function ps_open_image($psdoc, $type, $source, $data, $lenght, $width, $height, $components, $bpc, $params) {}
function ps_open_memory_image($psdoc, $gd) {}
function ps_place_image($psdoc, $imageid, $x, $y, $scale) {}
function ps_rect($psdoc, $x, $y, $width, $height) {}
function ps_restore($psdoc) {}
function ps_rotate($psdoc, $rot) {}
function ps_save($psdoc) {}
function ps_scale($psdoc, $x, $y) {}
function ps_set_border_color($psdoc, $red, $green, $blue) {}
function ps_set_border_dash($psdoc, $black, $white) {}
function ps_set_border_style($psdoc, $style, $width) {}
function ps_set_info($p, $key, $val) {}
function ps_set_parameter($psdoc, $name, $value) {}
function ps_set_text_pos($psdoc, $x, $y) {}
function ps_set_value($psdoc, $name, $value) {}
function ps_setcolor($psdoc, $type, $colorspace, $c1, $c2, $c3, $c4) {}
function ps_setdash($psdoc, $on, $off) {}
function ps_setflat($psdoc, $value) {}
function ps_setfont($psdoc, $fontid, $size) {}
function ps_setgray($psdoc, $gray) {}
function ps_setlinecap($psdoc, $type) {}
function ps_setlinejoin($psdoc, $type) {}
function ps_setlinewidth($psdoc, $width) {}
function ps_setmiterlimit($psdoc, $value) {}
function ps_setoverprintmode($psdoc, $mode) {}
function ps_setpolydash($psdoc, $arr) {}
function ps_shading_pattern($psdoc, $shadingid, $optlist) {}
function ps_shading($psdoc, $type, $x0, $y0, $x1, $y1, $c1, $c2, $c3, $c4, $optlist) {}
function ps_shfill($psdoc, $shadingid) {}
function ps_show_boxed($psdoc, $text, $left, $bottom, $width, $height, $hmode, $feature) {}
function ps_show_xy($psdoc, $text, $x, $y) {}
function ps_show_xy2($psdoc, $text, $len, $xcoor, $ycoor) {}
function ps_show($psdoc, $text) {}
function ps_show2($psdoc, $text, $len) {}
function ps_string_geometry($psdoc, $text, $fontid, $size) {}
function ps_stringwidth($psdoc, $text, $fontid, $size) {}
function ps_stroke($psdoc) {}
function ps_symbol_name($psdoc, $ord, $fontid) {}
function ps_symbol_width($psdoc, $ord, $fontid, $size) {}
function ps_symbol($psdoc, $ord) {}
function ps_translate($psdoc, $x, $y) {}
function pspell_add_to_personal($dictionary_link, $word) {}
function pspell_add_to_session($dictionary_link, $word) {}
function pspell_check($dictionary_link, $word) {}
function pspell_clear_session($dictionary_link) {}
function pspell_config_create($language, $spelling, $jargon, $encoding) {}
function pspell_config_data_dir($conf, $directory) {}
function pspell_config_dict_dir($conf, $directory) {}
function pspell_config_ignore($dictionary_link, $n) {}
function pspell_config_mode($dictionary_link, $mode) {}
function pspell_config_personal($dictionary_link, $file) {}
function pspell_config_repl($dictionary_link, $file) {}
function pspell_config_runtogether($dictionary_link, $flag) {}
function pspell_config_save_repl($dictionary_link, $flag) {}
function pspell_new_config($config) {}
function pspell_new_personal($personal, $language, $spelling, $jargon, $encoding, $mode) {}
function pspell_new($language, $spelling, $jargon, $encoding, $mode) {}
function pspell_save_wordlist($dictionary_link) {}
function pspell_store_replacement($dictionary_link, $misspelled, $correct) {}
function pspell_suggest($dictionary_link, $word) {}
function qdom_error() {}
function qdom_tree($doc) {}
function radius_acct_open() {}
function radius_add_server($radius_handle, $hostname, $port, $secret, $timeout, $max_tries) {}
function radius_auth_open() {}
function radius_close($radius_handle) {}
function radius_config($radius_handle, $file) {}
function radius_create_request($radius_handle, $type) {}
function radius_cvt_addr($data) {}
function radius_cvt_int($data) {}
function radius_cvt_string($data) {}
function radius_demangle_mppe_key($radius_handle, $mangled) {}
function radius_demangle($radius_handle, $mangled) {}
function radius_get_attr($radius_handle) {}
function radius_get_vendor_attr($data) {}
function radius_put_addr($radius_handle, $type, $addr) {}
function radius_put_attr($radius_handle, $type, $value) {}
function radius_put_int($radius_handle, $type, $value) {}
function radius_put_string($radius_handle, $type, $value) {}
function radius_put_vendor_addr($radius_handle, $vendor, $type, $addr) {}
function radius_put_vendor_attr($radius_handle, $vendor, $type, $value) {}
function radius_put_vendor_int($radius_handle, $vendor, $type, $value) {}
function radius_put_vendor_string($radius_handle, $vendor, $type, $value) {}
function radius_request_authenticator($radius_handle) {}
function radius_send_request($radius_handle) {}
function radius_server_secret($radius_handle) {}
function radius_strerror($radius_handle) {}
function rar_close($rar_file) {}
function rar_entry_get($rar_file, $entry_name) {}
function rar_list($rar_file) {}
function rar_open($filename, $password) {}
function readline_add_history($line) {}
function readline_callback_handler_install($prompt, $callback) {}
function readline_callback_handler_remove() {}
function readline_callback_read_char() {}
function readline_clear_history() {}
function readline_completion_function($function) {}
function readline_info($varname, $newvalue) {}
function readline_list_history() {}
function readline_on_new_line() {}
function readline_read_history($filename) {}
function readline_redisplay() {}
function readline_write_history($filename) {}
function readline($prompt) {}
function recode_file($request, $input, $output) {}
function recode_string($request, $string) {}
function ereg_replace($pattern, $replacement, $string) {}
function ereg($pattern, $string, $regs) {}
function eregi_replace($pattern, $replacement, $string) {}
function eregi($pattern, $string, $regs) {}
function split($pattern, $string, $limit) {}
function spliti($pattern, $string, $limit) {}
function sql_regcase($string) {}
function rpm_close($rpmr) {}
function rpm_get_tag($rpmr, $tagnum) {}
function rpm_is_valid($filename) {}
function rpm_open($filename) {}
function rpm_version() {}
function runkit_class_adopt($classname, $parentname) {}
function runkit_class_emancipate($classname) {}
function runkit_constant_add($constname, $value) {}
function runkit_constant_redefine($constname, $newvalue) {}
function runkit_constant_remove($constname) {}
function runkit_function_add($funcname, $arglist, $code) {}
function runkit_function_copy($funcname, $targetname) {}
function runkit_function_redefine($funcname, $arglist, $code) {}
function runkit_function_remove($funcname) {}
function runkit_function_rename($funcname, $newname) {}
function runkit_import($filename, $flags) {}
function runkit_lint_file($filename) {}
function runkit_lint($code) {}
function runkit_method_add($classname, $methodname, $args, $code, $flags) {}
function runkit_method_copy($dClass, $dMethod, $sClass, $sMethod) {}
function runkit_method_redefine($classname, $methodname, $args, $code, $flags) {}
function runkit_method_remove($classname, $methodname) {}
function runkit_method_rename($classname, $methodname, $newname) {}
function runkit_return_value_used() {}
function runkit_sandbox_output_handler($sandbox, $callback) {}
function runkit_superglobals() {}
function ftok($pathname, $proj) {}
function msg_get_queue($key, $perms) {}
function msg_queue_exists($key) {}
function msg_receive($queue, $desiredmsgtype, $msgtype, $maxsize, $message, $unserialize, $flags, $errorcode) {}
function msg_remove_queue($queue) {}
function msg_send($queue, $msgtype, $message, $serialize, $blocking, $errorcode) {}
function msg_set_queue($queue, $data) {}
function msg_stat_queue($queue) {}
function sem_acquire($sem_identifier) {}
function sem_get($key, $max_acquire, $perm, $auto_release) {}
function sem_release($sem_identifier) {}
function sem_remove($sem_identifier) {}
function shm_attach($key, $memsize, $perm) {}
function shm_detach($shm_identifier) {}
function shm_get_var($shm_identifier, $variable_key) {}
function shm_put_var($shm_identifier, $variable_key, $variable) {}
function shm_remove_var($shm_identifier, $variable_key) {}
function shm_remove($shm_identifier) {}
function session_cache_expire($new_cache_expire) {}
function session_cache_limiter($cache_limiter) {}
function session_decode($data) {}
function session_destroy() {}
function session_encode() {}
function session_get_cookie_params() {}
function session_id($id) {}
function session_is_registered($name) {}
function session_module_name($module) {}
function session_name($name) {}
function session_regenerate_id($delete_old_session) {}
function session_register($name) {}
function session_save_path($path) {}
function session_set_cookie_params($lifetime, $path, $domain, $secure, $httponly) {}
function session_set_save_handler($open, $close, $read, $write, $destroy, $gc) {}
function session_start() {}
function session_unregister($name) {}
function session_unset() {}
function session_write_close() {}
function session_pgsql_add_error($error_level, $error_message) {}
function session_pgsql_get_error($with_error_message) {}
function session_pgsql_get_field() {}
function session_pgsql_reset() {}
function session_pgsql_set_field($value) {}
function session_pgsql_status() {}
function shmop_close($shmid) {}
function shmop_delete($shmid) {}
function shmop_open($key, $flags, $mode, $size) {}
function shmop_read($shmid, $start, $count) {}
function shmop_size($shmid) {}
function shmop_write($shmid, $data, $offset) {}
function simplexml_import_dom($node, $class_name) {}
function simplexml_load_file($filename, $class_name, $options, $ns, $is_prefix) {}
function simplexml_load_string($data, $class_name, $options, $ns, $is_prefix) {}
function snmp_get_quick_print() {}
function snmp_get_valueretrieval() {}
function snmp_read_mib($filename) {}
function snmp_set_enum_print($enum_print) {}
function snmp_set_oid_numeric_print($oid_numeric_print) {}
function snmp_set_oid_output_format($oid_format) {}
function snmp_set_quick_print($quick_print) {}
function snmp_set_valueretrieval($method) {}
function snmpget($hostname, $community, $object_id, $timeout, $retries) {}
function snmpgetnext($host, $community, $object_id, $timeout, $retries) {}
function snmprealwalk($host, $community, $object_id, $timeout, $retries) {}
function snmpset($hostname, $community, $object_id, $type, $value, $timeout, $retries) {}
function snmpwalk($hostname, $community, $object_id, $timeout, $retries) {}
function snmpwalkoid($hostname, $community, $object_id, $timeout, $retries) {}
function is_soap_fault($obj) {}
function use_soap_error_handler($handler) {}
function socket_accept($socket) {}
function socket_bind($socket, $address, $port) {}
function socket_clear_error($socket) {}
function socket_close($socket) {}
function socket_connect($socket, $address, $port) {}
function socket_create_listen($port, $backlog) {}
function socket_create_pair($domain, $type, $protocol, $fd) {}
function socket_create($domain, $type, $protocol) {}
function socket_get_option($socket, $level, $optname) {}
function socket_getpeername($socket, $address, $port) {}
function socket_getsockname($socket, $addr, $port) {}
function socket_last_error($socket) {}
function socket_listen($socket, $backlog) {}
function socket_read($socket, $length, $type) {}
function socket_recv($socket, $buf, $len, $flags) {}
function socket_recvfrom($socket, $buf, $len, $flags, $name, $port) {}
function socket_select($read, $write, $except, $tv_sec, $tv_usec) {}
function socket_send($socket, $buf, $len, $flags) {}
function socket_sendto($socket, $buf, $len, $flags, $addr, $port) {}
function socket_set_block($socket) {}
function socket_set_nonblock($socket) {}
function socket_set_option($socket, $level, $optname, $optval) {}
function socket_shutdown($socket, $how) {}
function socket_strerror($errno) {}
function socket_write($socket, $buffer, $length) {}
function class_implements($class, $autoload) {}
function class_parents($class, $autoload) {}
function iterator_count($iterator) {}
function iterator_to_array($iterator, $use_keys) {}
function spl_autoload_call($class_name) {}
function spl_autoload_extensions($file_extensions) {}
function spl_autoload_functions() {}
function spl_autoload_register($autoload_function) {}
function spl_autoload_unregister($autoload_function) {}
function spl_autoload($class_name, $file_extensions) {}
function spl_classes() {}
function spl_object_hash($obj) {}
function calcul_hmac($clent, $siretcode, $price, $reference, $validity, $taxation, $devise, $language) {}
function calculhmac($clent, $data) {}
function nthmac($clent, $data) {}
function sqlite_array_query($dbhandle, $query, $result_type, $decode_binary) {}
function sqlite_busy_timeout($dbhandle, $milliseconds) {}
function sqlite_changes($dbhandle) {}
function sqlite_close($dbhandle) {}
function sqlite_column($result, $index_or_name, $decode_binary) {}
function sqlite_create_aggregate($dbhandle, $function_name, $step_func, $finalize_func, $num_args) {}
function sqlite_create_function($dbhandle, $function_name, $callback, $num_args) {}
function sqlite_current($result, $result_type, $decode_binary) {}
function sqlite_error_string($error_code) {}
function sqlite_escape_string($item) {}
function sqlite_exec($dbhandle, $query, $error_msg) {}
function sqlite_factory($filename, $mode, $error_message) {}
function sqlite_fetch_all($result, $result_type, $decode_binary) {}
function sqlite_fetch_array($result, $result_type, $decode_binary) {}
function sqlite_fetch_column_types($table_name, $dbhandle, $result_type) {}
function sqlite_fetch_object($result, $class_name, $ctor_params, $decode_binary) {}
function sqlite_fetch_single($result, $decode_binary) {}
function sqlite_field_name($result, $field_index) {}
function sqlite_has_more($result) {}
function sqlite_has_prev($result) {}
function sqlite_key($result) {}
function sqlite_last_error($dbhandle) {}
function sqlite_last_insert_rowid($dbhandle) {}
function sqlite_libencoding() {}
function sqlite_libversion() {}
function sqlite_next($result) {}
function sqlite_num_fields($result) {}
function sqlite_num_rows($result) {}
function sqlite_open($filename, $mode, $error_message) {}
function sqlite_popen($filename, $mode, $error_message) {}
function sqlite_prev($result) {}
function sqlite_query($dbhandle, $query, $result_type, $error_msg) {}
function sqlite_rewind($result) {}
function sqlite_seek($result, $rownum) {}
function sqlite_single_query($db, $query, $first_row_only, $decode_binary) {}
function sqlite_udf_decode_binary($data) {}
function sqlite_udf_encode_binary($data) {}
function sqlite_unbuffered_query($dbhandle, $query, $result_type, $error_msg) {}
function sqlite_valid($result) {}
function ssh2_auth_hostbased_file($session, $username, $hostname, $pubkeyfile, $privkeyfile, $passphrase, $local_username) {}
function ssh2_auth_none($session, $username) {}
function ssh2_auth_password($session, $username, $password) {}
function ssh2_auth_pubkey_file($session, $username, $pubkeyfile, $privkeyfile, $passphrase) {}
function ssh2_connect($host, $port, $methods, $callbacks) {}
function ssh2_exec($session, $command, $pty, $env, $width, $height, $width_height_type) {}
function ssh2_fetch_stream($channel, $streamid) {}
function ssh2_fingerprint($session, $flags) {}
function ssh2_methods_negotiated($session) {}
function ssh2_publickey_add($pkey, $algoname, $blob, $overwrite, $attributes) {}
function ssh2_publickey_init($session) {}
function ssh2_publickey_list($pkey) {}
function ssh2_publickey_remove($pkey, $algoname, $blob) {}
function ssh2_scp_recv($session, $remote_file, $local_file) {}
function ssh2_scp_send($session, $local_file, $remote_file, $create_mode) {}
function ssh2_sftp_lstat($sftp, $path) {}
function ssh2_sftp_mkdir($sftp, $dirname, $mode, $recursive) {}
function ssh2_sftp_readlink($sftp, $link) {}
function ssh2_sftp_realpath($sftp, $filename) {}
function ssh2_sftp_rename($sftp, $from, $to) {}
function ssh2_sftp_rmdir($sftp, $dirname) {}
function ssh2_sftp_stat($sftp, $path) {}
function ssh2_sftp_symlink($sftp, $target, $link) {}
function ssh2_sftp_unlink($sftp, $filename) {}
function ssh2_sftp($session) {}
function ssh2_shell($session, $term_type, $env, $width, $height, $width_height_type) {}
function ssh2_tunnel($session, $host, $port) {}
function stats_absolute_deviation($a) {}
function stats_cdf_beta($par1, $par2, $par3, $which) {}
function stats_cdf_binomial($par1, $par2, $par3, $which) {}
function stats_cdf_cauchy($par1, $par2, $par3, $which) {}
function stats_cdf_chisquare($par1, $par2, $which) {}
function stats_cdf_exponential($par1, $par2, $which) {}
function stats_cdf_f($par1, $par2, $par3, $which) {}
function stats_cdf_gamma($par1, $par2, $par3, $which) {}
function stats_cdf_laplace($par1, $par2, $par3, $which) {}
function stats_cdf_logistic($par1, $par2, $par3, $which) {}
function stats_cdf_negative_binomial($par1, $par2, $par3, $which) {}
function stats_cdf_noncentral_chisquare($par1, $par2, $par3, $which) {}
function stats_cdf_noncentral_f($par1, $par2, $par3, $par4, $which) {}
function stats_cdf_poisson($par1, $par2, $which) {}
function stats_cdf_t($par1, $par2, $which) {}
function stats_cdf_uniform($par1, $par2, $par3, $which) {}
function stats_cdf_weibull($par1, $par2, $par3, $which) {}
function stats_covariance($a, $b) {}
function stats_den_uniform($x, $a, $b) {}
function stats_dens_beta($x, $a, $b) {}
function stats_dens_cauchy($x, $ave, $stdev) {}
function stats_dens_chisquare($x, $dfr) {}
function stats_dens_exponential($x, $scale) {}
function stats_dens_f($x, $dfr1, $dfr2) {}
function stats_dens_gamma($x, $shape, $scale) {}
function stats_dens_laplace($x, $ave, $stdev) {}
function stats_dens_logistic($x, $ave, $stdev) {}
function stats_dens_negative_binomial($x, $n, $pi) {}
function stats_dens_normal($x, $ave, $stdev) {}
function stats_dens_pmf_binomial($x, $n, $pi) {}
function stats_dens_pmf_hypergeometric($n1, $n2, $N1, $N2) {}
function stats_dens_pmf_poisson($x, $lb) {}
function stats_dens_t($x, $dfr) {}
function stats_dens_weibull($x, $a, $b) {}
function stats_harmonic_mean($a) {}
function stats_kurtosis($a) {}
function stats_rand_gen_beta($a, $b) {}
function stats_rand_gen_chisquare($df) {}
function stats_rand_gen_exponential($av) {}
function stats_rand_gen_f($dfn, $dfd) {}
function stats_rand_gen_funiform($low, $high) {}
function stats_rand_gen_gamma($a, $r) {}
function stats_rand_gen_ibinomial_negative($n, $p) {}
function stats_rand_gen_ibinomial($n, $pp) {}
function stats_rand_gen_int() {}
function stats_rand_gen_ipoisson($mu) {}
function stats_rand_gen_iuniform($low, $high) {}
function stats_rand_gen_noncenral_chisquare($df, $xnonc) {}
function stats_rand_gen_noncentral_f($dfn, $dfd, $xnonc) {}
function stats_rand_gen_noncentral_t($df, $xnonc) {}
function stats_rand_gen_normal($av, $sd) {}
function stats_rand_gen_t($df) {}
function stats_rand_get_seeds() {}
function stats_rand_phrase_to_seeds($phrase) {}
function stats_rand_ranf() {}
function stats_rand_setall($iseed1, $iseed2) {}
function stats_skew($a) {}
function stats_standard_deviation($a, $sample) {}
function stats_stat_binomial_coef($x, $n) {}
function stats_stat_correlation($arr1, $arr2) {}
function stats_stat_gennch($n) {}
function stats_stat_independent_t($arr1, $arr2) {}
function stats_stat_innerproduct($arr1, $arr2) {}
function stats_stat_noncentral_t($par1, $par2, $par3, $which) {}
function stats_stat_paired_t($arr1, $arr2) {}
function stats_stat_percentile($df, $xnonc) {}
function stats_stat_powersum($arr, $power) {}
function stats_variance($a, $sample) {}
function stream_bucket_append($brigade, $bucket) {}
function stream_bucket_make_writeable($brigade) {}
function stream_bucket_new($stream, $buffer) {}
function stream_bucket_prepend($brigade, $bucket) {}
function stream_context_create($options, $params) {}
function stream_context_get_default($options) {}
function stream_context_get_options($stream_or_context) {}
function stream_context_set_default($options) {}
function stream_context_set_option($stream_or_context, $wrapper, $option, $value) {}
function stream_context_set_params($stream_or_context, $params) {}
function stream_copy_to_stream($source, $dest, $maxlength, $offset) {}
function stream_encoding($stream, $encoding) {}
function stream_filter_append($stream, $filtername, $read_write, $params) {}
function stream_filter_prepend($stream, $filtername, $read_write, $params) {}
function stream_filter_register($filtername, $classname) {}
function stream_filter_remove($stream_filter) {}
function stream_get_contents($handle, $maxlength, $offset) {}
function stream_get_filters() {}
function stream_get_line($handle, $length, $ending) {}
function stream_get_meta_data($stream) {}
function stream_get_transports() {}
function stream_get_wrappers() {}
function stream_notification_callback($notification_code, $severity, $message, $message_code, $bytes_transferred, $bytes_max) {}
function stream_resolve_include_path($filename, $context) {}
function stream_select($read, $write, $except, $tv_sec, $tv_usec) {}
function stream_set_blocking($stream, $mode) {}
function stream_set_timeout($stream, $seconds, $microseconds) {}
function stream_set_write_buffer($stream, $buffer) {}
function stream_socket_accept($server_socket, $timeout, $peername) {}
function stream_socket_client($remote_socket, $errno, $errstr, $timeout, $flags, $context) {}
function stream_socket_enable_crypto($stream, $enable, $crypto_type, $session_stream) {}
function stream_socket_get_name($handle, $want_peer) {}
function stream_socket_pair($domain, $type, $protocol) {}
function stream_socket_recvfrom($socket, $length, $flags, $address) {}
function stream_socket_sendto($socket, $data, $flags, $address) {}
function stream_socket_server($local_socket, $errno, $errstr, $flags, $context) {}
function stream_socket_shutdown($stream, $how) {}
function stream_wrapper_register($protocol, $classname) {}
function stream_wrapper_restore($protocol) {}
function stream_wrapper_unregister($protocol) {}
function addcslashes($str, $charlist) {}
function addslashes($str) {}
function bin2hex($str) {}
function chr($ascii) {}
function chunk_split($body, $chunklen, $end) {}
function convert_cyr_string($str, $from, $to) {}
function convert_uudecode($data) {}
function convert_uuencode($data) {}
function count_chars($string, $mode) {}
function crc32($str) {}
function crypt($str, $salt) {}
function explode($delimiter, $string, $limit) {}
function fprintf($handle, $format, $args) {}
function get_html_translation_table($table, $quote_style) {}
function hebrev($hebrew_text, $max_chars_per_line) {}
function hebrevc($hebrew_text, $max_chars_per_line) {}
function html_entity_decode($string, $quote_style, $charset) {}
function htmlentities($string, $quote_style, $charset, $double_encode) {}
function htmlspecialchars_decode($string, $quote_style) {}
function htmlspecialchars($string, $quote_style, $charset, $double_encode) {}
function implode($glue, $pieces) {}
function lcfirst($str) {}
function levenshtein($str1, $str2) {}
function localeconv() {}
function ltrim($str, $charlist) {}
function md5_file($filename, $raw_output) {}
function md5($str, $raw_output) {}
function metaphone($str, $phones) {}
function money_format($format, $number) {}
function nl_langinfo($item) {}
function nl2br($string, $is_xhtml) {}
function number_format($number, $decimals) {}
function ord($string) {}
function parse_str($str, $arr) {}
function printf($format, $args) {}
function quoted_printable_decode($str) {}
function quoted_printable_encode($str) {}
function quotemeta($str) {}
function rtrim($str, $charlist) {}
function setlocale($category, $locale) {}
function sha1_file($filename, $raw_output) {}
function sha1($str, $raw_output) {}
function similar_text($first, $second, $percent) {}
function soundex($str) {}
function sprintf($format, $args) {}
function sscanf($str, $format) {}
function str_getcsv($input, $delimiter, $enclosure, $escape) {}
function str_ireplace($search, $replace, $subject, $count) {}
function str_pad($input, $pad_length, $pad_string, $pad_type) {}
function str_repeat($input, $multiplier) {}
function str_replace($search, $replace, $subject, $count) {}
function str_rot13($str) {}
function str_shuffle($str) {}
function str_split($string, $split_length) {}
function str_word_count($string, $format, $charlist) {}
function strcasecmp($str1, $str2) {}
function strcmp($str1, $str2) {}
function strcoll($str1, $str2) {}
function strcspn($str1, $str2, $start, $length) {}
function strip_tags($str, $allowable_tags) {}
function stripcslashes($str) {}
function stripos($haystack, $needle, $offset) {}
function stripslashes($str) {}
function stristr($haystack, $needle, $before_needle) {}
function strlen($string) {}
function strnatcasecmp($str1, $str2) {}
function strnatcmp($str1, $str2) {}
function strncasecmp($str1, $str2, $len) {}
function strncmp($str1, $str2, $len) {}
function strpbrk($haystack, $char_list) {}
function strpos($haystack, $needle, $offset) {}
function strrchr($haystack, $needle) {}
function strrev($string) {}
function strripos($haystack, $needle, $offset) {}
function strrpos($haystack, $needle, $offset) {}
function strspn($str1, $str2, $start, $length) {}
function strstr($haystack, $needle, $before_needle) {}
function strtok($str, $token) {}
function strtolower($str) {}
function strtoupper($string) {}
function strtr($str, $from, $to) {}
function substr_compare($main_str, $str, $offset, $length, $case_insensitivity) {}
function substr_count($haystack, $needle, $offset, $length) {}
function substr_replace($string, $replacement, $start, $length) {}
function substr($string, $start, $length) {}
function trim($str, $charlist) {}
function ucfirst($str) {}
function ucwords($str) {}
function vfprintf($handle, $format, $args) {}
function vprintf($format, $args) {}
function vsprintf($format, $args) {}
function wordwrap($str, $width, $break, $cut) {}
function svn_add($path, $recursive, $force) {}
function svn_auth_get_parameter($key) {}
function svn_auth_set_parameter($key, $value) {}
function svn_cat($repos_url, $revision_no) {}
function svn_checkout($repos, $targetpath, $revision, $flags) {}
function svn_cleanup($workingdir) {}
function svn_client_version() {}
function svn_commit($log, $targets, $dontrecurse) {}
function svn_diff($path1, $rev1, $path2, $rev2) {}
function svn_fs_abort_txn($txn) {}
function svn_fs_apply_text($root, $path) {}
function svn_fs_begin_txn2($repos, $rev) {}
function svn_fs_change_node_prop($root, $path, $name, $value) {}
function svn_fs_check_path($fsroot, $path) {}
function svn_fs_contents_changed($root1, $path1, $root2, $path2) {}
function svn_fs_copy($from_root, $from_path, $to_root, $to_path) {}
function svn_fs_delete($root, $path) {}
function svn_fs_dir_entries($fsroot, $path) {}
function svn_fs_file_contents($fsroot, $path) {}
function svn_fs_file_length($fsroot, $path) {}
function svn_fs_is_dir($root, $path) {}
function svn_fs_is_file($root, $path) {}
function svn_fs_make_dir($root, $path) {}
function svn_fs_make_file($root, $path) {}
function svn_fs_node_created_rev($fsroot, $path) {}
function svn_fs_node_prop($fsroot, $path, $propname) {}
function svn_fs_props_changed($root1, $path1, $root2, $path2) {}
function svn_fs_revision_prop($fs, $revnum, $propname) {}
function svn_fs_revision_root($fs, $revnum) {}
function svn_fs_txn_root($txn) {}
function svn_fs_youngest_rev($fs) {}
function svn_import($path, $url, $nonrecursive) {}
function svn_log($repos_url, $start_revision, $end_revision, $limit, $flags) {}
function svn_ls($repos_url, $revision_no, $recurse) {}
function svn_repos_create($path, $config, $fsconfig) {}
function svn_repos_fs_begin_txn_for_commit($repos, $rev, $author, $log_msg) {}
function svn_repos_fs_commit_txn($txn) {}
function svn_repos_fs($repos) {}
function svn_repos_hotcopy($repospath, $destpath, $cleanlogs) {}
function svn_repos_open($path) {}
function svn_repos_recover($path) {}
function svn_status($path, $flags) {}
function svn_update($path, $revno, $recurse) {}
function swf_actiongeturl($url, $target) {}
function swf_actiongotoframe($framenumber) {}
function swf_actiongotolabel($label) {}
function swf_actionnextframe() {}
function swf_actionplay() {}
function swf_actionprevframe() {}
function swf_actionsettarget($target) {}
function swf_actionstop() {}
function swf_actiontogglequality() {}
function swf_actionwaitforframe($framenumber, $skipcount) {}
function swf_addbuttonrecord($states, $shapeid, $depth) {}
function swf_addcolor($r, $g, $b, $a) {}
function swf_closefile($return_file) {}
function swf_definebitmap($objid, $image_name) {}
function swf_definefont($fontid, $fontname) {}
function swf_defineline($objid, $x1, $y1, $x2, $y2, $width) {}
function swf_definepoly($objid, $coords, $npoints, $width) {}
function swf_definerect($objid, $x1, $y1, $x2, $y2, $width) {}
function swf_definetext($objid, $str, $docenter) {}
function swf_endbutton() {}
function swf_enddoaction() {}
function swf_endshape() {}
function swf_endsymbol() {}
function swf_fontsize($size) {}
function swf_fontslant($slant) {}
function swf_fonttracking($tracking) {}
function swf_getbitmapinfo($bitmapid) {}
function swf_getfontinfo() {}
function swf_getframe() {}
function swf_labelframe($name) {}
function swf_lookat($view_x, $view_y, $view_z, $reference_x, $reference_y, $reference_z, $twist) {}
function swf_modifyobject($depth, $how) {}
function swf_mulcolor($r, $g, $b, $a) {}
function swf_nextid() {}
function swf_oncondition($transition) {}
function swf_openfile($filename, $width, $height, $framerate, $r, $g, $b) {}
function swf_ortho($xmin, $xmax, $ymin, $ymax, $zmin, $zmax) {}
function swf_ortho2($xmin, $xmax, $ymin, $ymax) {}
function swf_perspective($fovy, $aspect, $near, $far) {}
function swf_placeobject($objid, $depth) {}
function swf_polarview($dist, $azimuth, $incidence, $twist) {}
function swf_popmatrix() {}
function swf_posround($round) {}
function swf_pushmatrix() {}
function swf_removeobject($depth) {}
function swf_rotate($angle, $axis) {}
function swf_scale($x, $y, $z) {}
function swf_setfont($fontid) {}
function swf_setframe($framenumber) {}
function swf_shapearc($x, $y, $r, $ang1, $ang2) {}
function swf_shapecurveto($x1, $y1, $x2, $y2) {}
function swf_shapecurveto3($x1, $y1, $x2, $y2, $x3, $y3) {}
function swf_shapefillbitmapclip($bitmapid) {}
function swf_shapefillbitmaptile($bitmapid) {}
function swf_shapefilloff() {}
function swf_shapefillsolid($r, $g, $b, $a) {}
function swf_shapelinesolid($r, $g, $b, $a, $width) {}
function swf_shapelineto($x, $y) {}
function swf_shapemoveto($x, $y) {}
function swf_showframe() {}
function swf_startbutton($objid, $type) {}
function swf_startdoaction() {}
function swf_startshape($objid) {}
function swf_startsymbol($objid) {}
function swf_textwidth($str) {}
function swf_translate($x, $y, $z) {}
function swf_viewport($xmin, $xmax, $ymin, $ymax) {}
function sybase_affected_rows($link_identifier) {}
function sybase_close($link_identifier) {}
function sybase_connect($servername, $username, $password, $charset, $appname) {}
function sybase_data_seek($result_identifier, $row_number) {}
function sybase_deadlock_retry_count($retry_count) {}
function sybase_fetch_array($result) {}
function sybase_fetch_assoc($result) {}
function sybase_fetch_field($result, $field_offset) {}
function sybase_fetch_object($result, $object) {}
function sybase_fetch_row($result) {}
function sybase_field_seek($result, $field_offset) {}
function sybase_free_result($result) {}
function sybase_get_last_message() {}
function sybase_min_client_severity($severity) {}
function sybase_min_error_severity($severity) {}
function sybase_min_message_severity($severity) {}
function sybase_min_server_severity($severity) {}
function sybase_num_fields($result) {}
function sybase_num_rows($result) {}
function sybase_pconnect($servername, $username, $password, $charset, $appname) {}
function sybase_query($query, $link_identifier) {}
function sybase_result($result, $row, $field) {}
function sybase_select_db($database_name, $link_identifier) {}
function sybase_set_message_handler($handler, $connection) {}
function sybase_unbuffered_query($query, $link_identifier, $store_result) {}
function tcpwrap_check($daemon, $address, $user, $nodns) {}
function ob_tidyhandler($input, $mode) {}
function tidy_access_count($object) {}
function tidy_clean_repair($object) {}
function tidy_config_count($object) {}
function tidy_diagnose($object) {}
function tidy_error_count($object) {}
function tidy_get_body($object) {}
function tidy_get_config($object) {}
function tidy_get_error_buffer($object) {}
function tidy_get_head($object) {}
function tidy_get_html_ver($object) {}
function tidy_get_html($object) {}
function tidy_get_opt_doc($object, $optname) {}
function tidy_get_output($object) {}
function tidy_get_release() {}
function tidy_get_root($object) {}
function tidy_get_status($object) {}
function tidy_getopt($object, $option) {}
function tidy_is_xhtml($object) {}
function tidy_is_xml($object) {}
function tidy_load_config($filename, $encoding) {}
function tidy_parse_file($filename, $config, $encoding, $use_include_path) {}
function tidy_parse_string($input, $config, $encoding) {}
function tidy_repair_file($filename, $config, $encoding, $use_include_path) {}
function tidy_repair_string($data, $config, $encoding) {}
function tidy_reset_config() {}
function tidy_save_config($filename) {}
function tidy_set_encoding($encoding) {}
function tidy_setopt($option, $value) {}
function tidy_warning_count($object) {}
function token_get_all($source) {}
function token_name($token) {}
function unicode_decode($input, $encoding, $errmode) {}
function unicode_encode($input, $encoding, $errmode) {}
function unicode_get_error_mode($direction) {}
function unicode_get_subst_char() {}
function unicode_set_error_mode($direction, $mode) {}
function unicode_set_subst_char($character) {}
function odbc_autocommit($connection_id, $OnOff) {}
function odbc_binmode($result_id, $mode) {}
function odbc_close_all() {}
function odbc_close($connection_id) {}
function odbc_columnprivileges($connection_id, $qualifier, $owner, $table_name, $column_name) {}
function odbc_columns($connection_id, $qualifier, $schema, $table_name, $column_name) {}
function odbc_commit($connection_id) {}
function odbc_connect($dsn, $user, $password, $cursor_type) {}
function odbc_cursor($result_id) {}
function odbc_data_source($connection_id, $fetch_type) {}
function odbc_error($connection_id) {}
function odbc_errormsg($connection_id) {}
function odbc_exec($connection_id, $query_string, $flags) {}
function odbc_execute($result_id, $parameters_array) {}
function odbc_fetch_array($result, $rownumber) {}
function odbc_fetch_into($result_id, $result_array, $rownumber) {}
function odbc_fetch_object($result, $rownumber) {}
function odbc_fetch_row($result_id, $row_number) {}
function odbc_field_len($result_id, $field_number) {}
function odbc_field_name($result_id, $field_number) {}
function odbc_field_num($result_id, $field_name) {}
function odbc_field_scale($result_id, $field_number) {}
function odbc_field_type($result_id, $field_number) {}
function odbc_foreignkeys($connection_id, $pk_qualifier, $pk_owner, $pk_table, $fk_qualifier, $fk_owner, $fk_table) {}
function odbc_free_result($result_id) {}
function odbc_gettypeinfo($connection_id, $data_type) {}
function odbc_longreadlen($result_id, $length) {}
function odbc_next_result($result_id) {}
function odbc_num_fields($result_id) {}
function odbc_num_rows($result_id) {}
function odbc_pconnect($dsn, $user, $password, $cursor_type) {}
function odbc_prepare($connection_id, $query_string) {}
function odbc_primarykeys($connection_id, $qualifier, $owner, $table) {}
function odbc_procedurecolumns($connection_id) {}
function odbc_procedures($connection_id) {}
function odbc_result_all($result_id, $format) {}
function odbc_result($result_id, $field) {}
function odbc_rollback($connection_id) {}
function odbc_setoption($id, $function, $option, $param) {}
function odbc_specialcolumns($connection_id, $type, $qualifier, $owner, $table, $scope, $nullable) {}
function odbc_statistics($connection_id, $qualifier, $owner, $table_name, $unique, $accuracy) {}
function odbc_tableprivileges($connection_id, $qualifier, $owner, $name) {}
function odbc_tables($connection_id, $qualifier, $owner, $name, $types) {}
function base64_decode($data, $strict) {}
function base64_encode($data) {}
function get_headers($url, $format) {}
function get_meta_tags($filename, $use_include_path) {}
function http_build_query($formdata, $numeric_prefix, $arg_separator) {}
function parse_url($url, $component) {}
function rawurldecode($str) {}
function rawurlencode($str) {}
function urldecode($str) {}
function urlencode($str) {}
function debug_zval_dump($variable) {}
function floatval($var) {}
function get_defined_vars() {}
function get_resource_type($handle) {}
function gettype($var) {}
function import_request_variables($types, $prefix) {}
function intval($var, $base) {}
function is_array($var) {}
function is_binary($var) {}
function is_bool($var) {}
function is_buffer($var) {}
function is_callable($var, $syntax_only, $callable_name) {}
function is_float($var) {}
function is_int($var) {}
function is_null($var) {}
function is_numeric($var) {}
function is_object($var) {}
function is_resource($var) {}
function is_scalar($var) {}
function is_string($var) {}
function is_unicode($var) {}
function print_r($expression, $return) {}
function serialize($value) {}
function settype($var, $type) {}
function strval($var) {}
function unserialize($str) {}
function var_dump($expression, $expression) {}
function var_export($expression, $return) {}
function vpopmail_add_alias_domain_ex($olddomain, $newdomain) {}
function vpopmail_add_alias_domain($domain, $aliasdomain) {}
function vpopmail_add_domain_ex($domain, $passwd, $quota, $bounce, $apop) {}
function vpopmail_add_domain($domain, $dir, $uid, $gid) {}
function vpopmail_add_user($user, $domain, $password, $gecos, $apop) {}
function vpopmail_alias_add($user, $domain, $alias) {}
function vpopmail_alias_del_domain($domain) {}
function vpopmail_alias_del($user, $domain) {}
function vpopmail_alias_get_all($domain) {}
function vpopmail_alias_get($alias, $domain) {}
function vpopmail_auth_user($user, $domain, $password, $apop) {}
function vpopmail_del_domain_ex($domain) {}
function vpopmail_del_domain($domain) {}
function vpopmail_del_user($user, $domain) {}
function vpopmail_error() {}
function vpopmail_passwd($user, $domain, $password, $apop) {}
function vpopmail_set_user_quota($user, $domain, $quota) {}
function w32api_deftype($typename, $member1_type, $member1_name) {}
function w32api_init_dtype($typename, $value) {}
function w32api_invoke_function($funcname, $argument) {}
function w32api_register_function($library, $function_name, $return_type) {}
function w32api_set_call_method($method) {}
function wddx_add_vars($packet_id, $var_name) {}
function wddx_packet_end($packet_id) {}
function wddx_packet_start($comment) {}
function wddx_serialize_value($var, $comment) {}
function wddx_serialize_vars($var_name) {}
function wddx_unserialize($packet) {}
function win32_ps_list_procs() {}
function win32_ps_stat_mem() {}
function win32_ps_stat_proc($pid) {}
function win32_create_service($details, $machine) {}
function win32_delete_service($servicename, $machine) {}
function win32_get_last_control_message() {}
function win32_query_service_status($servicename, $machine) {}
function win32_set_service_status($status) {}
function win32_start_service_ctrl_dispatcher($name) {}
function win32_start_service($servicename, $machine) {}
function win32_stop_service($servicename, $machine) {}
function xattr_get($filename, $name, $flags) {}
function xattr_list($filename, $flags) {}
function xattr_remove($filename, $name, $flags) {}
function xattr_set($filename, $name, $value, $flags) {}
function xattr_supported($filename, $flags) {}
function xdiff_file_bdiff_size($file) {}
function xdiff_file_bdiff($old_file, $new_file, $dest) {}
function xdiff_file_bpatch($file, $patch, $dest) {}
function xdiff_file_diff_binary($old_file, $new_file, $dest) {}
function xdiff_file_diff($old_file, $new_file, $dest, $context, $minimal) {}
function xdiff_file_merge3($old_file, $new_file1, $new_file2, $dest) {}
function xdiff_file_patch_binary($file, $patch, $dest) {}
function xdiff_file_patch($file, $patch, $dest, $flags) {}
function xdiff_file_rabdiff($old_file, $new_file, $dest) {}
function xdiff_string_bdiff_size($patch) {}
function xdiff_string_bdiff($old_data, $new_data) {}
function xdiff_string_bpatch($str, $patch) {}
function xdiff_string_diff($old_data, $new_data, $context, $minimal) {}
function xdiff_string_merge3($old_data, $new_data1, $new_data2, $error) {}
function xdiff_string_patch_binary($str, $patch) {}
function xdiff_string_patch($str, $patch, $flags, $error) {}
function utf8_decode($data) {}
function utf8_encode($data) {}
function xml_error_string($code) {}
function xml_get_current_byte_index($parser) {}
function xml_get_current_column_number($parser) {}
function xml_get_current_line_number($parser) {}
function xml_get_error_code($parser) {}
function xml_parse_into_struct($parser, $data, $values, $index) {}
function xml_parse($parser, $data, $is_final) {}
function xml_parser_create_ns($encoding, $separator) {}
function xml_parser_create($encoding) {}
function xml_parser_free($parser) {}
function xml_parser_get_option($parser, $option) {}
function xml_parser_set_option($parser, $option, $value) {}
function xml_set_character_data_handler($parser, $handler) {}
function xml_set_default_handler($parser, $handler) {}
function xml_set_element_handler($parser, $start_element_handler, $end_element_handler) {}
function xml_set_end_namespace_decl_handler($parser, $handler) {}
function xml_set_external_entity_ref_handler($parser, $handler) {}
function xml_set_notation_decl_handler($parser, $handler) {}
function xml_set_object($parser, $object) {}
function xml_set_processing_instruction_handler($parser, $handler) {}
function xml_set_start_namespace_decl_handler($parser, $handler) {}
function xml_set_unparsed_entity_decl_handler($parser, $handler) {}
function xmlrpc_decode_request($xml, $method, $encoding) {}
function xmlrpc_decode($xml, $encoding) {}
function xmlrpc_encode_request($method, $params, $output_options) {}
function xmlrpc_encode($value) {}
function xmlrpc_get_type($value) {}
function xmlrpc_is_fault($arg) {}
function xmlrpc_parse_method_descriptions($xml) {}
function xmlrpc_server_add_introspection_data($server, $desc) {}
function xmlrpc_server_call_method($server, $xml, $user_data, $output_options) {}
function xmlrpc_server_create() {}
function xmlrpc_server_destroy($server) {}
function xmlrpc_server_register_introspection_callback($server, $function) {}
function xmlrpc_server_register_method($server, $method_name, $function) {}
function xmlrpc_set_type($value, $type) {}
function xmlwriter_end_attribute($xmlwriter) {}
function xmlwriter_end_cdata($xmlwriter) {}
function xmlwriter_end_comment($xmlwriter) {}
function xmlwriter_end_document($xmlwriter) {}
function xmlwriter_end_dtd_attlist($xmlwriter) {}
function xmlwriter_end_dtd_element($xmlwriter) {}
function xmlwriter_end_dtd_entity($xmlwriter) {}
function xmlwriter_end_dtd($xmlwriter) {}
function xmlwriter_end_element($xmlwriter) {}
function xmlwriter_end_pi($xmlwriter) {}
function xmlwriter_flush($xmlwriter, $empty) {}
function xmlwriter_full_end_element($xmlwriter) {}
function xmlwriter_open_memory() {}
function xmlwriter_open_uri($uri) {}
function xmlwriter_output_memory($xmlwriter, $flush) {}
function xmlwriter_set_indent_string($xmlwriter, $indentString) {}
function xmlwriter_set_indent($xmlwriter, $indent) {}
function xmlwriter_start_attribute_ns($xmlwriter, $prefix, $name, $uri) {}
function xmlwriter_start_attribute($xmlwriter, $name) {}
function xmlwriter_start_cdata($xmlwriter) {}
function xmlwriter_start_comment($xmlwriter) {}
function xmlwriter_start_document($xmlwriter, $version, $encoding, $standalone) {}
function xmlwriter_start_dtd_attlist($xmlwriter, $name) {}
function xmlwriter_start_dtd_element($xmlwriter, $qualifiedName) {}
function xmlwriter_start_dtd_entity($xmlwriter, $name, $isparam) {}
function xmlwriter_start_dtd($xmlwriter, $qualifiedName, $publicId, $systemId) {}
function xmlwriter_start_element_ns($xmlwriter, $prefix, $name, $uri) {}
function xmlwriter_start_element($xmlwriter, $name) {}
function xmlwriter_start_pi($xmlwriter, $target) {}
function xmlwriter_text($xmlwriter, $content) {}
function xmlwriter_write_attribute_ns($xmlwriter, $prefix, $name, $uri, $content) {}
function xmlwriter_write_attribute($xmlwriter, $name, $value) {}
function xmlwriter_write_cdata($xmlwriter, $content) {}
function xmlwriter_write_comment($xmlwriter, $content) {}
function xmlwriter_write_dtd_attlist($xmlwriter, $name, $content) {}
function xmlwriter_write_dtd_element($xmlwriter, $name, $content) {}
function xmlwriter_write_dtd_entity($xmlwriter, $name, $content) {}
function xmlwriter_write_dtd($xmlwriter, $name, $publicId, $systemId, $subset) {}
function xmlwriter_write_element_ns($xmlwriter, $prefix, $name, $uri, $content) {}
function xmlwriter_write_element($xmlwriter, $name, $content) {}
function xmlwriter_write_pi($xmlwriter, $target, $content) {}
function xmlwriter_write_raw($xmlwriter, $content) {}
function xslt_backend_info() {}
function xslt_backend_name() {}
function xslt_backend_version() {}
function xslt_create() {}
function xslt_errno($xh) {}
function xslt_error($xh) {}
function xslt_free($xh) {}
function xslt_getopt($processor) {}
function xslt_process($xh, $xmlcontainer, $xslcontainer, $resultcontainer, $arguments, $parameters) {}
function xslt_set_base($xh, $uri) {}
function xslt_set_encoding($xh, $encoding) {}
function xslt_set_error_handler($xh, $handler) {}
function xslt_set_log($xh, $log) {}
function xslt_set_object($processor, $obj) {}
function xslt_set_sax_handler($xh, $handlers) {}
function xslt_set_sax_handlers($processor, $handlers) {}
function xslt_set_scheme_handler($xh, $handlers) {}
function xslt_set_scheme_handlers($xh, $handlers) {}
function xslt_setopt($processor, $newmask) {}
function yaz_addinfo($id) {}
function yaz_ccl_conf($id, $config) {}
function yaz_ccl_parse($id, $query, $result) {}
function yaz_close($id) {}
function yaz_connect($zurl, $options) {}
function yaz_database($id, $databases) {}
function yaz_element($id, $elementset) {}
function yaz_errno($id) {}
function yaz_error($id) {}
function yaz_es_result($id) {}
function yaz_es($id, $type, $args) {}
function yaz_get_option($id, $name) {}
function yaz_hits($id, $searchresult) {}
function yaz_itemorder($id, $args) {}
function yaz_present($id) {}
function yaz_range($id, $start, $number) {}
function yaz_record($id, $pos, $type) {}
function yaz_scan_result($id, $result) {}
function yaz_scan($id, $type, $startterm, $flags) {}
function yaz_schema($id, $schema) {}
function yaz_search($id, $type, $query) {}
function yaz_set_option($id, $name, $value) {}
function yaz_sort($id, $criteria) {}
function yaz_syntax($id, $syntax) {}
function yaz_wait($options) {}
function zip_close($zip) {}
function zip_entry_close($zip_entry) {}
function zip_entry_compressedsize($zip_entry) {}
function zip_entry_compressionmethod($zip_entry) {}
function zip_entry_filesize($zip_entry) {}
function zip_entry_name($zip_entry) {}
function zip_entry_open($zip, $zip_entry, $mode) {}
function zip_entry_read($zip_entry, $length) {}
function zip_open($filename) {}
function zip_read($zip) {}
function gzclose($zp) {}
function gzcompress($data, $level) {}
function gzdecode($data, $length) {}
function gzdeflate($data, $level) {}
function gzencode($data, $level, $encoding_mode) {}
function gzeof($zp) {}
function gzfile($filename, $use_include_path) {}
function gzgetc($zp) {}
function gzgets($zp, $length) {}
function gzgetss($zp, $length, $allowable_tags) {}
function gzinflate($data, $length) {}
function gzopen($filename, $mode, $use_include_path) {}
function gzpassthru($zp) {}
function gzread($zp, $length) {}
function gzrewind($zp) {}
function gzseek($zp, $offset) {}
function gztell($zp) {}
function gzuncompress($data, $length) {}
function gzwrite($zp, $string, $length) {}
function readgzfile($filename, $use_include_path) {}
function zlib_get_coding_type() {}
class ErrorException {
    function getSeverity() {}
}
class Exception {
    function __clone() {}
    function getCode() {}
    function getFile() {}
    function getLine() {}
    function getMessage() {}
    function getTrace() {}
    function getTraceAsString() {}
    function __toString() {}
}
class DomAttr {
    function __construct($name, $value) {}
    function isId() {}
}
class DomCharacterData {
    function appendData($data) {}
    function deleteData($offset, $count) {}
    function insertData($offset, $data) {}
    function replaceData($offset, $count, $data) {}
    function substringData($offset, $count) {}
}
class DomDocument {
    function __construct($version, $encoding) {}
    function createAttribute($name) {}
    function createAttributeNS($namespaceURI, $qualifiedName) {}
    function createCDATASection($data) {}
    function createComment($data) {}
    function createDocumentFragment() {}
    function createElement($name, $value) {}
    function createElementNS($namespaceURI, $qualifiedName, $value) {}
    function createEntityReference($name) {}
    function createProcessingInstruction($target, $data) {}
    function createTextNode($content) {}
    function getElementById($elementId) {}
    function getElementsByTagName($name) {}
    function getElementsByTagNameNS($namespaceURI, $localName) {}
    function importNode($importedNode, $deep) {}
    function load($filename, $options) {}
    function loadHTML($source) {}
    function loadHTMLFile($filename) {}
    function loadXML($source, $options) {}
    function normalizeDocument() {}
    function registerNodeClass($baseclass, $extendedclass) {}
    function relaxNGValidate($filename) {}
    function relaxNGValidateSource($source) {}
    function save($filename, $options) {}
    function saveHTML() {}
    function saveHTMLFile($filename) {}
    function saveXML($node, $options) {}
    function schemaValidate($filename) {}
    function schemaValidateSource($source) {}
    function validate() {}
    function xinclude($options) {}
    function add_root($name) {}
    function create_attribute($name, $value) {}
    function create_cdata_section($content) {}
    function create_comment($content) {}
    function create_element_ns($uri, $name, $prefix) {}
    function create_element($name) {}
    function create_entity_reference($content) {}
    function create_processing_instruction($content) {}
    function create_text_node($content) {}
    function doctype() {}
    function document_element() {}
    function dump_file($filename, $compressionmode, $format) {}
    function dump_mem($format, $encoding) {}
    function get_element_by_id($id) {}
    function get_elements_by_tagname($name) {}
    function html_dump_mem() {}
}
class DomDocumentFragment {
    function appendXML($data) {}
}
class DomElement {
    function getAttribute($name) {}
    function getAttributeNode($name) {}
    function getAttributeNodeNS($namespaceURI, $localName) {}
    function getAttributeNS($namespaceURI, $localName) {}
    function getElementsByTagName($name) {}
    function getElementsByTagNameNS($namespaceURI, $localName) {}
    function hasAttribute($name) {}
    function hasAttributeNS($namespaceURI, $localName) {}
    function removeAttribute($name) {}
    function removeAttributeNode($oldnode) {}
    function removeAttributeNS($namespaceURI, $localName) {}
    function setAttribute($name, $value) {}
    function setAttributeNode($attr) {}
    function setAttributeNodeNS($attr) {}
    function setAttributeNS($namespaceURI, $qualifiedName, $value) {}
    function setIdAttribute($name, $isId) {}
    function setIdAttributeNode($attr, $isId) {}
    function setIdAttributeNS($namespaceURI, $localName, $isId) {}
}
class DomImplementation {
    function createDocument($namespaceURI, $qualifiedName, $doctype) {}
    function createDocumentType($qualifiedName, $publicId, $systemId) {}
    function hasFeature($feature, $version) {}
}
class DomNamedNodeMap {
    function getNamedItem($name) {}
    function getNamedItemNS($namespaceURI, $localName) {}
    function item($index) {}
}
class DomNode {
    function appendChild($newnode) {}
    function cloneNode($deep) {}
    function hasAttributes() {}
    function hasChildNodes() {}
    function insertBefore($newnode, $refnode) {}
    function isDefaultNamespace($namespaceURI) {}
    function isSameNode($node) {}
    function isSupported($feature, $version) {}
    function lookupNamespaceURI($prefix) {}
    function lookupPrefix($namespaceURI) {}
    function normalize() {}
    function removeChild($oldnode) {}
    function replaceChild($newnode, $oldnode) {}
    function append_sibling($newnode) {}
    function attributes() {}
    function child_nodes() {}
    function clone_node() {}
    function dump_node() {}
    function first_child() {}
    function get_content() {}
    function has_attributes() {}
    function has_child_nodes() {}
    function insert_before($newnode, $refnode) {}
    function is_blank_node() {}
    function last_child() {}
    function next_sibling() {}
    function node_name() {}
    function node_type() {}
    function node_value() {}
    function owner_document() {}
    function parent_node() {}
    function prefix() {}
    function previous_sibling() {}
    function remove_child($oldchild) {}
    function replace_child($newnode, $oldnode) {}
    function replace_node($newnode) {}
    function set_content($content) {}
    function set_name() {}
    function set_namespace($uri, $prefix) {}
    function unlink_node() {}
}
class DomNodelist {
    function item($index) {}
}
class DomText {
    function isWhitespaceInElementContent() {}
    function splitText($offset) {}
}
class DomXPath {
    function evaluate($expression, $contextnode) {}
    function query($expression, $contextnode) {}
    function registerNamespace($prefix, $namespaceURI) {}
}
class HaruAnnotation {
    function setBorderStyle($width, $dash_on, $dash_off) {}
    function setHighlightMode($mode) {}
    function setIcon($icon) {}
    function setOpened($opened) {}
}
class HaruDestination {
    function setFit() {}
    function setFitB() {}
    function setFitBH($top) {}
    function setFitBV($left) {}
    function setFitH($top) {}
    function setFitR($left, $bottom, $right, $top) {}
    function setFitV($left) {}
    function setXYZ($left, $top, $zoom) {}
}
class HaruDoc {
    function addPage() {}
    function addPageLabel($first_page, $style, $first_num, $prefix) {}
    function __construct() {}
    function createOutline($title, $parent_outline, $encoder) {}
    function getCurrentEncoder() {}
    function getCurrentPage() {}
    function getEncoder($encoding) {}
    function getFont($fontname, $encoding) {}
    function getInfoAttr($type) {}
    function getPageLayout() {}
    function getPageMode() {}
    function getStreamSize() {}
    function insertPage($page) {}
    function loadJPEG($filename) {}
    function loadPNG($filename, $deferred) {}
    function loadRaw($filename, $width, $height, $color_space) {}
    function loadTTC($fontfile, $index, $embed) {}
    function loadTTF($fontfile, $embed) {}
    function loadType1($afmfile, $pfmfile) {}
    function output() {}
    function readFromStream($bytes) {}
    function resetError() {}
    function resetStream() {}
    function save($file) {}
    function saveToStream() {}
    function setCompressionMode($mode) {}
    function setCurrentEncoder($encoding) {}
    function setEncryptionMode($mode, $key_len) {}
    function setInfoAttr($type, $info) {}
    function setInfoDateAttr($type, $year, $month, $day, $hour, $min, $sec, $ind, $off_hour, $off_min) {}
    function setOpenAction($destination) {}
    function setPageLayout($layout) {}
    function setPageMode($mode) {}
    function setPagesConfiguration($page_per_pages) {}
    function setPassword($owner_password, $user_password) {}
    function setPermission($permission) {}
    function useCNSEncodings() {}
    function useCNSFonts() {}
    function useCNTEncodings() {}
    function useCNTFonts() {}
    function useJPEncodings() {}
    function useJPFonts() {}
    function useKREncodings() {}
    function useKRFonts() {}
}
class HaruEncoder {
    function getByteType($text, $index) {}
    function getType() {}
    function getUnicode($character) {}
    function getWritingMode() {}
}
class HaruFont {
    function getAscent() {}
    function getCapHeight() {}
    function getDescent() {}
    function getEncodingName() {}
    function getFontName() {}
    function getTextWidth($text) {}
    function getUnicodeWidth($character) {}
    function getXHeight() {}
    function measureText($text, $width, $font_size, $char_space, $word_space, $word_wrap) {}
}
class HaruImage {
    function getBitsPerComponent() {}
    function getColorSpace() {}
    function getHeight() {}
    function getSize() {}
    function getWidth() {}
    function setColorMask($rmin, $rmax, $gmin, $gmax, $bmin, $bmax) {}
    function setMaskImage($mask_image) {}
}
class HaruOutline {
    function setDestination($destination) {}
    function setOpened($opened) {}
}
class HaruPage {
    function circle($x, $y, $ray) {}
    function arc($x, $y, $ray, $ang1, $ang2) {}
    function beginText() {}
    function closePath() {}
    function concat($a, $b, $c, $d, $x, $y) {}
    function createDestination() {}
    function createLinkAnnotation($rectangle, $destination) {}
    function createTextAnnotation($rectangle, $text, $encoder) {}
    function createURLAnnotation($rectangle, $url) {}
    function curveTo($x1, $y1, $x2, $y2, $x3, $y3) {}
    function curveTo2($x2, $y2, $x3, $y3) {}
    function curveTo3($x1, $y1, $x3, $y3) {}
    function drawImage($image, $x, $y, $width, $height) {}
    function ellipse($x, $y, $xray, $yray) {}
    function endPath() {}
    function endText() {}
    function eofill() {}
    function eoFillStroke($close_path) {}
    function fill() {}
    function fillStroke($close_path) {}
    function getCharSpace() {}
    function getCMYKFill() {}
    function getCMYKStroke() {}
    function getCurrentFont() {}
    function getCurrentFontSize() {}
    function getCurrentPos() {}
    function getCurrentTextPos() {}
    function getDash() {}
    function getFillingColorSpace() {}
    function getFlatness() {}
    function getGMode() {}
    function getGrayFill() {}
    function getGrayStroke() {}
    function getHeight() {}
    function getHorizontalScaling() {}
    function getLineCap() {}
    function getLineJoin() {}
    function getLineWidth() {}
    function getMiterLimit() {}
    function getRGBFill() {}
    function getRGBStroke() {}
    function getStrokingColorSpace() {}
    function getTextLeading() {}
    function getTextMatrix() {}
    function getTextRenderingMode() {}
    function getTextRise() {}
    function getTextWidth($text) {}
    function getTransMatrix() {}
    function getWidth() {}
    function getWordSpace() {}
    function lineTo($x, $y) {}
    function measureText($text, $width, $wordwrap) {}
    function moveTextPos($x, $y, $set_leading) {}
    function moveTo($x, $y) {}
    function moveToNextLine() {}
    function rectangle($x, $y, $width, $height) {}
    function setCharSpace($char_space) {}
    function setCMYKFill($c, $m, $y, $k) {}
    function setCMYKStroke($c, $m, $y, $k) {}
    function setDash($pattern, $phase) {}
    function setFlatness($flatness) {}
    function setFontAndSize($font, $size) {}
    function setGrayFill($value) {}
    function setGrayStroke($value) {}
    function setHeight($height) {}
    function setHorizontalScaling($scaling) {}
    function setLineCap($cap) {}
    function setLineJoin($join) {}
    function setLineWidth($width) {}
    function setMiterLimit($limit) {}
    function setRGBFill($r, $g, $b) {}
    function setRGBStroke($r, $g, $b) {}
    function setRotate($angle) {}
    function setSize($size, $direction) {}
    function setSlideShow($type, $disp_time, $trans_time) {}
    function setTextLeading($text_leading) {}
    function setTextMatrix($a, $b, $c, $d, $x, $y) {}
    function setTextRenderingMode($mode) {}
    function setTextRise($rise) {}
    function setWidth($width) {}
    function setWordSpace($word_space) {}
    function showText($text) {}
    function showTextNextLine($text, $word_space, $char_space) {}
    function stroke($close_path) {}
    function textOut($x, $y, $text) {}
    function textRect($left, $top, $right, $bottom, $text, $align) {}
}
class HttpMessage {
    function addHeaders($headers, $append = FALSE) {}
    function __construct($message) {}
    function detach() {}
    function factory($raw_message, $class_name = 'HttpMessage') {}
    function fromEnv($message_type, $class_name = 'HttpMessage') {}
    function fromString($raw_message, $class_name = 'HttpMessage') {}
    function getBody() {}
    function getHeader($header) {}
    function getHeaders() {}
    function getHttpVersion() {}
    function getParentMessage() {}
    function getRequestMethod() {}
    function getRequestUrl() {}
    function getResponseCode() {}
    function getResponseStatus() {}
    function getType() {}
    function guessContentType($magic_file, $magic_mode = MAGIC_MIME) {}
    function prepend($message, $top = TRUE) {}
    function reverse() {}
    function send() {}
    function setBody($body) {}
    function setHeaders($headers) {}
    function setHttpVersion($version) {}
    function setRequestMethod($method) {}
    function setRequestUrl($url) {}
    function setResponseCode($code) {}
    function setResponseStatus($status) {}
    function setType($type) {}
    function toMessageTypeObject() {}
    function toString($include_parent = FALSE) {}
}
class HttpDeflateStream {
    function __construct($flags = 0) {}
    function factory($flags = 0, $class_name = 'HttpDeflateStream') {}
    function finish($data) {}
    function flush($data) {}
    function update($data) {}
}
class HttpInflateStream {
    function __construct($flags = 0) {}
    function factory($flags = 0, $class_name = 'HttpInflateStream') {}
    function finish($data) {}
    function flush($data) {}
    function update($data) {}
}
class HttpQueryString {
    function __construct($global = TRUE, $add) {}
    function get($key, $type = 0, $defval = NULL, $delete = FALSE) {}
    function mod($params) {}
    function set($params) {}
    function singleton($global = TRUE) {}
    function toArray() {}
    function toString() {}
    function xlate($ie, $oe) {}
}
class HttpRequest {
    function addCookies($cookies) {}
    function addHeaders($headers) {}
    function addPostFields($post_data) {}
    function addPostFile($name, $file, $content_type = 'applicationxoctetstream') {}
    function addPutData($put_data) {}
    function addQueryData($query_params) {}
    function addRawPostData($raw_post_data) {}
    function addSslOptions($options) {}
    function clearHistory() {}
    function __construct($url, $request_method = HTTP_METH_GET, $options) {}
    function enableCookies() {}
    function getContentType() {}
    function getCookies() {}
    function getHeaders() {}
    function getHistory() {}
    function getMethod() {}
    function getOptions() {}
    function getPostFields() {}
    function getPostFiles() {}
    function getPutData() {}
    function getPutFile() {}
    function getQueryData() {}
    function getRawPostData() {}
    function getRawRequestMessage() {}
    function getRawResponseMessage() {}
    function getRequestMessage() {}
    function getResponseBody() {}
    function getResponseCode() {}
    function getResponseCookies($flags, $allowed_extras) {}
    function getResponseData() {}
    function getResponseHeader($name) {}
    function getResponseInfo($name) {}
    function getResponseMessage() {}
    function getResponseStatus() {}
    function getSslOptions() {}
    function getUrl() {}
    function resetCookies($session_only = FALSE) {}
    function send() {}
    function setContentType($content_type) {}
    function setCookies($cookies) {}
    function setHeaders($headers) {}
    function setMethod($request_method) {}
    function setOptions($options) {}
    function setPostFields($post_data) {}
    function setPostFiles($post_files) {}
    function setPutData($put_data) {}
    function setPutFile($file) {}
    function setQueryData($query_data) {}
    function setRawPostData($raw_post_data) {}
    function setSslOptions($options) {}
    function setUrl($url) {}
}
class HttpRequestPool {
    function attach($request) {}
    function __construct($request) {}
    function __destruct() {}
    function detach($request) {}
    function getAttachedRequests() {}
    function getFinishedRequests() {}
    function reset() {}
    function send() {}
    function socketPerform() {}
    function socketSelect() {}
}
class HttpResponse {
    function capture() {}
    function getBufferSize() {}
    function getCache() {}
    function getCacheControl() {}
    function getContentDisposition() {}
    function getContentType() {}
    function getData() {}
    function getETag() {}
    function getFile() {}
    function getGzip() {}
    function getHeader($name) {}
    function getLastModified() {}
    function getRequestBody() {}
    function getRequestBodyStream() {}
    function getRequestHeaders() {}
    function getStream() {}
    function getThrottleDelay() {}
    function guessContentType($magic_file, $magic_mode=MAGIC_MIME) {}
    function redirect($url, $params, $session = FALSE, $status) {}
    function send($clean_ob = TRUE) {}
    function setBufferSize($bytes) {}
    function setCache($cache) {}
    function setCacheControl($control, $max_age = 0, $must_revalidate = TRUE) {}
    function setContentDisposition($filename, $inline = FALSE) {}
    function setContentType($content_type) {}
    function setData($data) {}
    function setETag($etag) {}
    function setFile($file) {}
    function setGzip($gzip) {}
    function setHeader($name, $value, $replace = TRUE) {}
    function setLastModified($timestamp) {}
    function setStream($stream) {}
    function setThrottleDelay($seconds) {}
    function status($status) {}
}
class Imagick {
    function adaptiveBlurImage($radius, $sigma, $channel) {}
    function adaptiveResizeImage($columns, $rows, $fit) {}
    function adaptiveSharpenImage($radius, $sigma, $channel) {}
    function adaptiveThresholdImage($width, $height, $offset) {}
    function addImage($source) {}
    function addNoiseImage($noise_type, $channel) {}
    function affineTransformImage($matrix) {}
    function annotateImage($draw_settings, $x, $y, $angle, $text) {}
    function appendImages($stack) {}
    function averageImages() {}
    function blackThresholdImage($threshold) {}
    function blurImage($radius, $sigma, $channel) {}
    function borderImage($bordercolor, $width, $height) {}
    function charcoalImage($radius, $sigma) {}
    function chopImage($width, $height, $x, $y) {}
    function clear() {}
    function clipImage() {}
    function clipPathImage($pathname, $inside) {}
    function clutImage($lookup_table, $channel) {}
    function coalesceImages() {}
    function colorFloodfillImage($fill, $fuzz, $bordercolor, $x, $y) {}
    function colorizeImage($colorize, $opacity) {}
    function combineImages($channelType) {}
    function commentImage($comment) {}
    function compareImageChannels($image, $channelType, $metricType) {}
    function compareImageLayers($method) {}
    function compareImages($compare, $metric) {}
    function compositeImage($composite_object, $composite, $x, $y, $channel) {}
    function __construct($files) {}
    function contrastImage($sharpen) {}
    function contrastStretchImage($black_point, $white_point, $channel) {}
    function convolveImage($kernel, $channel) {}
    function cropImage($width, $height, $x, $y) {}
    function cropThumbnailImage($width, $height) {}
    function current() {}
    function cycleColormapImage($displace) {}
    function deconstructImages() {}
    function despeckleImage() {}
    function destroy() {}
    function displayImage($servername) {}
    function displayImages($servername) {}
    function distortImage($method, $arguments, $bestfit) {}
    function drawImage($draw) {}
    function edgeImage($radius) {}
    function embossImage($radius, $sigma) {}
    function enhanceImage() {}
    function equalizeImage() {}
    function evaluateImage($op, $constant, $channel) {}
    function flattenImages() {}
    function flipImage() {}
    function flopImage() {}
    function frameImage($matte_color, $width, $height, $inner_bevel, $outer_bevel) {}
    function fxImage($expression, $channel) {}
    function gammaImage($gamma, $channel) {}
    function gaussianBlurImage($radius, $sigma, $channel) {}
    function getCompression() {}
    function getCompressionQuality() {}
    function getCopyright() {}
    function getFilename() {}
    function getFormat() {}
    function getHomeURL() {}
    function getImage() {}
    function getImageBackgroundColor() {}
    function getImageBlob() {}
    function getImageBluePrimary($x, $y) {}
    function getImageBorderColor() {}
    function getImageChannelDepth($channelType) {}
    function getImageChannelDistortion($reference, $channel, $metric) {}
    function getImageChannelExtrema($channel) {}
    function getImageChannelMean($channel) {}
    function getImageChannelStatistics() {}
    function getImageColormapColor($index) {}
    function getImageColors() {}
    function getImageColorspace() {}
    function getImageCompose() {}
    function getImageDelay() {}
    function getImageDepth() {}
    function getImageDispose() {}
    function getImageDistortion($reference, $metric) {}
    function getImageExtrema() {}
    function getImageFilename() {}
    function getImageFormat() {}
    function getImageGamma() {}
    function getImageGeometry() {}
    function getImageGreenPrimary() {}
    function getImageHeight() {}
    function getImageHistogram() {}
    function getImageIndex() {}
    function getImageInterlaceScheme() {}
    function getImageInterpolateMethod() {}
    function getImageIterations() {}
    function getImageLength() {}
    function getImageMagickLicense() {}
    function getImageMatte() {}
    function getImageMatteColor() {}
    function getImageOrientation() {}
    function getImagePage() {}
    function getImagePixelColor($x, $y) {}
    function getImageProfile($name) {}
    function getImageProfiles($pattern, $only_names) {}
    function getImageProperties($pattern, $only_names) {}
    function getImageProperty($name) {}
    function getImageRedPrimary() {}
    function getImageRegion($width, $height, $x, $y) {}
    function getImageRenderingIntent() {}
    function getImageResolution() {}
    function getImageScene() {}
    function getImageSignature() {}
    function getImageSize() {}
    function getImageTicksPerSecond() {}
    function getImageTotalInkDensity() {}
    function getImageType() {}
    function getImageUnits() {}
    function getImageVirtualPixelMethod() {}
    function getImageWhitePoint() {}
    function getImageWidth() {}
    function getInterlaceScheme() {}
    function getIteratorIndex() {}
    function getNumberImages() {}
    function getOption($key) {}
    function getPackageName() {}
    function getPage() {}
    function getPixelIterator() {}
    function getPixelRegionIterator($x, $y, $columns, $rows) {}
    function getQuantumDepth() {}
    function getQuantumRange() {}
    function getReleaseDate() {}
    function getResource($type) {}
    function getResourceLimit($type) {}
    function getSamplingFactors() {}
    function getSize() {}
    function getSizeOffset() {}
    function getVersion() {}
    function hasNextImage() {}
    function hasPreviousImage() {}
    function identifyImage($appendRawOutput) {}
    function implodeImage($radius) {}
    function labelImage($label) {}
    function levelImage($blackPoint, $gamma, $whitePoint, $channel) {}
    function linearStretchImage($blackPoint, $whitePoint) {}
    function magnifyImage() {}
    function mapImage($map, $dither) {}
    function matteFloodfillImage($alpha, $fuzz, $bordercolor, $x, $y) {}
    function medianFilterImage($radius) {}
    function minifyImage() {}
    function modulateImage($brightness, $saturation, $hue) {}
    function montageImage($draw, $tile_geometry, $thumbnail_geometry, $mode, $frame) {}
    function morphImages($number_frames) {}
    function mosaicImages() {}
    function motionBlurImage($radius, $sigma, $angle) {}
    function negateImage($gray, $channel) {}
    function newImage($cols, $rows, $background, $format) {}
    function newPseudoImage($columns, $rows, $pseudoString) {}
    function nextImage() {}
    function normalizeImage($channel) {}
    function oilPaintImage($radius) {}
    function optimizeImageLayers() {}
    function paintFloodfillImage($fill, $fuzz, $bordercolor, $x, $y) {}
    function paintOpaqueImage($target, $fill, $fuzz, $channel) {}
    function paintTransparentImage($target, $alpha, $fuzz) {}
    function pingImage($filename) {}
    function pingImageBlob($image) {}
    function pingImageFile($filehandle, $fileName) {}
    function polaroidImage($properties, $angle) {}
    function posterizeImage($levels, $dither) {}
    function previewImages($preview) {}
    function previousImage() {}
    function profileImage($name, $profile) {}
    function quantizeImage($numberColors, $colorspace, $treedepth, $dither, $measureError) {}
    function quantizeImages($numberColors, $colorspace, $treedepth, $dither, $measureError) {}
    function queryFontMetrics($properties, $text, $multiline) {}
    function queryFonts($pattern) {}
    function queryFormats($pattern) {}
    function radialBlurImage($angle, $channel) {}
    function raiseImage($width, $height, $x, $y, $raise) {}
    function randomThresholdImage($low, $high, $channel) {}
    function readImage($filename) {}
    function readImageBlob($image, $filename) {}
    function readImageFile($filehandle, $fileName) {}
    function reduceNoiseImage($radius) {}
    function removeImage() {}
    function removeImageProfile($name) {}
    function render() {}
    function resampleImage($x_resolution, $y_resolution, $filter, $blur) {}
    function resizeImage($columns, $rows, $filter, $blur, $fit) {}
    function rollImage($x, $y) {}
    function rotateImage($background, $degrees) {}
    function roundCorners($x_rounding, $y_rounding, $stroke_width, $displace, $size_correction) {}
    function sampleImage($columns, $rows) {}
    function scaleImage($cols, $rows, $fit) {}
    function separateImageChannel($channel) {}
    function sepiaToneImage($threshold) {}
    function setBackgroundColor($background) {}
    function setCompression($compression) {}
    function setCompressionQuality($quality) {}
    function setFilename($filename) {}
    function setFirstIterator() {}
    function setFont($font) {}
    function setFormat($format) {}
    function setImage($replace) {}
    function setImageBackgroundColor($background) {}
    function setImageBias($bias) {}
    function setImageBluePrimary($x, $y) {}
    function setImageBorderColor($border) {}
    function setImageChannelDepth($channel, $depth) {}
    function setImageColormapColor($index, $color) {}
    function setImageColorspace($colorspace) {}
    function setImageCompose($compose) {}
    function setImageCompression($compression) {}
    function setImageDelay($delay) {}
    function setImageDepth($depth) {}
    function setImageDispose($dispose) {}
    function setImageExtent($columns, $rows) {}
    function setImageFilename($filename) {}
    function setImageFormat($format) {}
    function setImageGamma($gamma) {}
    function setImageGreenPrimary($x, $y) {}
    function setImageIndex($index) {}
    function setImageInterlaceScheme($interlace_scheme) {}
    function setImageInterpolateMethod($method) {}
    function setImageIterations($iterations) {}
    function setImageMatte($matte) {}
    function setImageMatteColor($matte) {}
    function setImageOpacity($opacity) {}
    function setImageOrientation($orientation) {}
    function setImagePage($width, $height, $x, $y) {}
    function setImageProfile($name, $profile) {}
    function setImageProperty($name, $value) {}
    function setImageRedPrimary($x, $y) {}
    function setImageRenderingIntent($rendering_intent) {}
    function setImageResolution($x_resolution, $y_resolution) {}
    function setImageScene($scene) {}
    function setImageTicksPerSecond($ticks_persecond) {}
    function setImageType($image_type) {}
    function setImageUnits($units) {}
    function setImageVirtualPixelMethod($method) {}
    function setImageWhitePoint($x, $y) {}
    function setInterlaceScheme($interlace_scheme) {}
    function setIteratorIndex($index) {}
    function setLastIterator() {}
    function setOption($key, $value) {}
    function setPage($width, $height, $x, $y) {}
    function setResolution($x_resolution, $y_resolution) {}
    function setResourceLimit($type, $limit) {}
    function setSamplingFactors($factors) {}
    function setSize($columns, $rows) {}
    function setSizeOffset($columns, $rows, $offset) {}
    function setType($image_type) {}
    function shadeImage($gray, $azimuth, $elevation) {}
    function shadowImage($opacity, $sigma, $x, $y) {}
    function sharpenImage($radius, $sigma, $channel) {}
    function shaveImage($columns, $rows) {}
    function shearImage($background, $x_shear, $y_shear) {}
    function sigmoidalContrastImage($sharpen, $alpha, $beta, $channel) {}
    function sketchImage($radius, $sigma, $angle) {}
    function solarizeImage($threshold) {}
    function spliceImage($width, $height, $x, $y) {}
    function spreadImage($radius) {}
    function steganoImage($watermark_wand, $offset) {}
    function stereoImage($offset_wand) {}
    function stripImage() {}
    function swirlImage($degrees) {}
    function textureImage($texture_wand) {}
    function thresholdImage($threshold, $channel) {}
    function thumbnailImage($columns, $rows, $fit) {}
    function tintImage($tint, $opacity) {}
    function transformImage($crop, $geometry) {}
    function transverseImage() {}
    function trimImage($fuzz) {}
    function uniqueImageColors() {}
    function unsharpMaskImage($radius, $sigma, $amount, $threshold, $channel) {}
    function valid() {}
    function vignetteImage($blackPoint, $whitePoint, $x, $y) {}
    function waveImage($amplitude, $length) {}
    function whiteThresholdImage($threshold) {}
    function writeImage($filename) {}
    function writeImages($filename, $adjoin) {}
}
class ImagickDraw {
    function affine($affine) {}
    function annotation($x, $y, $text) {}
    function arc($sx, $sy, $ex, $ey, $sd, $ed) {}
    function bezier($coordinates) {}
    function circle($ox, $oy, $px, $py) {}
    function clear() {}
    function color($x, $y, $paintMethod) {}
    function comment($comment) {}
    function composite($compose, $x, $y, $width, $height, $compositeWand) {}
    function __construct() {}
    function destroy() {}
    function ellipse($ox, $oy, $rx, $ry, $start, $end) {}
    function getClipPath() {}
    function getClipRule() {}
    function getClipUnits() {}
    function getFillColor() {}
    function getFillOpacity() {}
    function getFillRule() {}
    function getFont() {}
    function getFontFamily() {}
    function getFontSize() {}
    function getFontStyle() {}
    function getFontWeight() {}
    function getGravity() {}
    function getStrokeAntialias() {}
    function getStrokeColor($stroke_color) {}
    function getStrokeDashArray() {}
    function getStrokeDashOffset() {}
    function getStrokeLineCap() {}
    function getStrokeLineJoin() {}
    function getStrokeMiterLimit() {}
    function getStrokeOpacity() {}
    function getStrokeWidth() {}
    function getTextAlignment() {}
    function getTextAntialias() {}
    function getTextDecoration() {}
    function getTextEncoding() {}
    function getTextUnderColor() {}
    function getVectorGraphics() {}
    function line($sx, $sy, $ex, $ey) {}
    function matte($x, $y, $paintMethod) {}
    function pathClose() {}
    function pathCurveToAbsolute($x1, $y1, $x2, $y2, $x, $y) {}
    function pathCurveToQuadraticBezierAbsolute($x1, $y1, $x, $y) {}
    function pathCurveToQuadraticBezierRelative($x1, $y1, $x, $y) {}
    function pathCurveToQuadraticBezierSmoothAbsolute($x, $y) {}
    function pathCurveToQuadraticBezierSmoothRelative($x, $y) {}
    function pathCurveToRelative($x1, $y1, $x2, $y2, $x, $y) {}
    function pathCurveToSmoothAbsolute($x2, $y2, $x, $y) {}
    function pathCurveToSmoothRelative($x2, $y2, $x, $y) {}
    function pathEllipticArcAbsolute($rx, $ry, $x_axis_rotation, $large_arc_flag, $sweep_flag, $x, $y) {}
    function pathEllipticArcRelative($rx, $ry, $x_axis_rotation, $large_arc_flag, $sweep_flag, $x, $y) {}
    function pathFinish() {}
    function pathLineToAbsolute($x, $y) {}
    function pathLineToHorizontalAbsolute($x) {}
    function pathLineToHorizontalRelative($x) {}
    function pathLineToRelative($x, $y) {}
    function pathLineToVerticalAbsolute($y) {}
    function pathLineToVerticalRelative($y) {}
    function pathMoveToAbsolute($x, $y) {}
    function pathMoveToRelative($x, $y) {}
    function pathStart() {}
    function point($x, $y) {}
    function polygon($coordinates) {}
    function polyline($coordinates) {}
    function pop() {}
    function popClipPath() {}
    function popDefs() {}
    function popPattern() {}
    function push() {}
    function pushClipPath($clip_mask_id) {}
    function pushDefs() {}
    function pushPattern($pattern_id, $x, $y, $width, $height) {}
    function rectangle($x1, $y1, $x2, $y2) {}
    function render() {}
    function rotate($degrees) {}
    function roundRectangle($x1, $y1, $x2, $y2, $rx, $ry) {}
    function scale($x, $y) {}
    function setClipPath($clip_mask) {}
    function setClipRule($fill_rule) {}
    function setClipUnits($clip_units) {}
    function setFillAlpha($opacity) {}
    function setFillColor($fill_pixel) {}
    function setFillOpacity($fillOpacity) {}
    function setFillPatternURL($fill_url) {}
    function setFillRule($fill_rule) {}
    function setFont($font_name) {}
    function setFontFamily($font_family) {}
    function setFontSize($pointsize) {}
    function setFontStretch($fontStretch) {}
    function setFontStyle($style) {}
    function setFontWeight($font_weight) {}
    function setGravity($gravity) {}
    function setStrokeAlpha($opacity) {}
    function setStrokeAntialias($stroke_antialias) {}
    function setStrokeColor($stroke_pixel) {}
    function setStrokeDashArray($dashArray) {}
    function setStrokeDashOffset($dash_offset) {}
    function setStrokeLineCap($linecap) {}
    function setStrokeLineJoin($linejoin) {}
    function setStrokeMiterLimit($miterlimit) {}
    function setStrokeOpacity($stroke_opacity) {}
    function setStrokePatternURL($stroke_url) {}
    function setStrokeWidth($stroke_width) {}
    function setTextAlignment($alignment) {}
    function setTextAntialias($antiAlias) {}
    function setTextDecoration($decoration) {}
    function setTextEncoding($encoding) {}
    function setTextUnderColor($under_color) {}
    function setVectorGraphics($xml) {}
    function setViewbox($x1, $y1, $x2, $y2) {}
    function skewX($degrees) {}
    function skewY($degrees) {}
    function translate($x, $y) {}
}
class ImagickPixel {
    function clear() {}
    function __construct($color) {}
    function destroy() {}
    function getColor($normalized) {}
    function getColorAsString() {}
    function getColorCount() {}
    function getColorValue($color) {}
    function getHSL() {}
    function isSimilar($color, $fuzz) {}
    function setColor($color) {}
    function setColorValue($color, $value) {}
    function setHSL($hue, $saturation, $luminosity) {}
}
class ImagickPixelIterator {
    function clear() {}
    function __construct($wand) {}
    function destroy() {}
    function getCurrentIteratorRow() {}
    function getIteratorRow() {}
    function getNextIteratorRow() {}
    function getPreviousIteratorRow() {}
    function newPixelIterator($wand) {}
    function newPixelRegionIterator($wand, $x, $y, $columns, $rows) {}
    function resetIterator() {}
    function setIteratorFirstRow() {}
    function setIteratorLastRow() {}
    function setIteratorRow($row) {}
    function syncIterator() {}
}
class Collator {
    function asort($arr, $sort_flag) {}
    function compare($str1, $str2) {}
    function create($locale) {}
    function getAttribute($attr) {}
    function getErrorCode() {}
    function getErrorMessage() {}
    function getLocale($type) {}
    function getStrength() {}
    function setAttribute($attr, $val) {}
    function setStrength($strength) {}
    function sortWithSortKeys($arr) {}
    function sort($arr, $sort_flag) {}
}
class IntlDateFormatter {
    function create($locale, $datetype, $timetype, $timezone, $calendar, $pattern) {}
    function format($value) {}
    function getCalendar() {}
    function getDateType() {}
    function getErrorCode() {}
    function getErrorMessage() {}
    function getLocale($which) {}
    function getPattern() {}
    function getTimeType() {}
    function getTimeZoneId() {}
    function isLenient() {}
    function localtime($value, $position) {}
    function parse($value, $position) {}
    function setCalendar($which) {}
    function setLenient($lenient) {}
    function setPattern($pattern) {}
    function setTimeZoneId($zone) {}
}
class Locale {
    function acceptFromHttp($header) {}
    function composeLocale($subtags) {}
    function filterMatches($langtag, $locale) {}
    function getAllVariants($locale) {}
    function getDefault() {}
    function getDisplayLanguage($locale, $in_locale) {}
    function getDisplayName($locale, $in_locale) {}
    function getDisplayRegion($locale, $in_locale) {}
    function getDisplayScript($locale, $in_locale) {}
    function getDisplayVariant($locale, $in_locale) {}
    function getKeywords($locale) {}
    function getPrimaryLanguage($locale) {}
    function getRegion($locale) {}
    function getScript($locale) {}
    function lookup($langtag, $locale, $default) {}
    function parseLocale($locale) {}
    function setDefault($locale) {}
}
class MessageFormatter {
    function create($locale, $pattern) {}
    function formatMessage($locale, $pattern, $args) {}
    function format($args) {}
    function getErrorCode() {}
    function getErrorMessage() {}
    function getLocale() {}
    function getPattern() {}
    function parseMessage($locale, $value) {}
    function parse($value) {}
    function setPattern($pattern) {}
}
class Normalizer {
    function isNormalized($input, $form) {}
    function normalize($input, $form) {}
}
class NumberFormatter {
    function create($locale, $style, $pattern) {}
    function formatCurrency($value, $currency) {}
    function format($value, $type) {}
    function getAttribute($attr) {}
    function getErrorCode() {}
    function getErrorMessage() {}
    function getLocale($type) {}
    function getPattern() {}
    function getSymbol($attr) {}
    function getTextAttribute($attr) {}
    function parseCurrency($value, $currency, $position) {}
    function parse($value, $type, $position) {}
    function setAttribute($attr, $value) {}
    function setPattern($pattern) {}
    function setSymbol($attr, $value) {}
    function setTextAttribute($attr, $value) {}
}
class Memcache {
    function add($key, $var, $flag, $expire) {}
    function addServer($host, $port, $persistent, $weight, $timeout, $retry_interval, $status, $failure_callback) {}
    function close() {}
    function connect($host, $port, $timeout) {}
    function decrement($key, $value) {}
    function delete($key, $timeout) {}
    function flush() {}
    function get($key, $flags) {}
    function getExtendedStats($type, $slabid, $limit) {}
    function getServerStatus($host, $port) {}
    function getStats($type, $slabid, $limit) {}
    function getVersion() {}
    function increment($key, $value) {}
    function pconnect($host, $port, $timeout) {}
    function replace($key, $var, $flag, $expire) {}
    function set($key, $var, $flag, $expire) {}
    function setCompressThreshold($threshold, $min_savings) {}
    function setServerParams($host, $port, $timeout, $retry_interval, $status, $failure_callback) {}
}
class mysqli {
    function autocommit($mode) {}
    function change_user($user, $password, $database) {}
    function character_set_name() {}
    function close() {}
    function commit() {}
    function debug($message) {}
    function dump_debug_info() {}
    function get_charset() {}
    function get_client_info() {}
    function get_client_version() {}
    function get_warnings() {}
    function kill($processid) {}
    function more_results() {}
    function multi_query($query) {}
    function next_result() {}
    function options($option, $value) {}
    function ping() {}
    function query($query, $resultmode) {}
    function real_connect($host, $username, $passwd, $dbname, $port, $socket, $flags) {}
    function escape_string($escapestr) {}
    function rollback() {}
    function select_db($dbname) {}
    function set_charset($charset) {}
    function ssl_set($key, $cert, $ca, $capath, $cipher) {}
    function stat() {}
}
class mysqli_driver {
    function embedded_server_end() {}
    function embedded_server_start($start, $arguments, $groups) {}
}
class mysqli_result {
    function data_seek($offset) {}
    function fetch_array($resulttype) {}
    function fetch_assoc() {}
    function fetch_field_direct($fieldnr) {}
    function fetch_field() {}
    function fetch_fields() {}
    function fetch_object($class_name, $params) {}
    function fetch_row() {}
    function field_seek($fieldnr) {}
    function free() {}
}
class mysqli_stmt {
    function bind_param($types, $var1) {}
    function bind_result($var1) {}
    function close() {}
    function data_seek($offset) {}
    function execute() {}
    function fetch() {}
    function free_result() {}
    function get_warnings($stmt) {}
    function prepare($query) {}
    function reset() {}
    function result_metadata() {}
    function send_long_data($param_nr, $data) {}
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
    function beginTransaction() {}
    function commit() {}
    function errorCode() {}
    function errorInfo() {}
    function exec($statement) {}
    function getAttribute($attribute) {}
    function getAvailableDrivers() {}
    function lastInsertId($name) {}
    function prepare($statement, $driver_options) {}
    function query($statement) {}
    function quote($string, $parameter_type) {}
    function rollBack() {}
    function setAttribute($attribute, $value) {}
    function pgsqlLOBCreate() {}
    function pgsqlLOBOpen($oid, $mode) {}
    function pgsqlLOBUnlink($oid) {}
}
class PDOStatement {
    function bindColumn($column, $param, $type, $maxlen, $driverdata) {}
    function bindParam($parameter, $variable, $data_type, $length, $driver_options) {}
    function bindValue($parameter, $value, $data_type) {}
    function closeCursor() {}
    function columnCount() {}
    function errorCode() {}
    function errorInfo() {}
    function execute($input_parameters) {}
    function fetch($fetch_style, $cursor_orientation, $cursor_offset) {}
    function fetchAll($fetch_style, $column_index, $ctor_args) {}
    function fetchColumn($column_number) {}
    function fetchObject($class_name, $ctor_args) {}
    function getAttribute($attribute) {}
    function getColumnMeta($column) {}
    function nextRowset() {}
    function rowCount() {}
    function setAttribute($attribute, $value) {}
    function setFetchMode($mode) {}
}
class Phar {
    function addEmptyDir($dirname) {}
    function addFile($file, $localname) {}
    function addFromString($localname, $contents) {}
    function apiVersion() {}
    function buildFromDirectory($base_dir, $regex) {}
    function buildFromIterator($iter, $base_directory) {}
    function canCompress($type) {}
    function canWrite() {}
    function compress($compression, $extension) {}
    function compressAllFilesBZIP2() {}
    function compressAllFilesGZ() {}
    function compressFiles($compression) {}
    function __construct($fname, $flags, $alias) {}
    function convertToData($format, $compression, $extension) {}
    function convertToExecutable($format, $compression, $extension) {}
    function copy($oldfile, $newfile) {}
    function count() {}
    function createDefaultStub() {}
    function decompress($extension) {}
    function decompressFiles() {}
    function delMetadata() {}
    function delete($entry) {}
    function extractTo($pathto, $files, $overwrite) {}
    function getMetaData() {}
    function getModified() {}
    function getSignature() {}
    function getStub() {}
    function getSupportedCompression() {}
    function getSupportedSignatures() {}
    function getVersion() {}
    function hasMetadata() {}
    function interceptFileFuncs() {}
    function isBuffering() {}
    function isCompressed() {}
    function isFileFormat($format) {}
    function isValidPharFilename($filename, $executable) {}
    function isWritable() {}
    function loadPhar($filename, $alias) {}
    function mapPhar($alias, $dataoffset) {}
    function mount($pharpath, $externalpath) {}
    function mungServer($munglist) {}
    function offsetExists($offset) {}
    function offsetGet($offset) {}
    function offsetSet($offset, $value) {}
    function offsetUnset($offset) {}
    function running($retphar) {}
    function setAlias($alias) {}
    function setDefaultStub($index, $webindex) {}
    function setMetadata($metadata) {}
    function setSignatureAlgorithm($sigtype, $privatekey) {}
    function setStub($stub) {}
    function startBuffering() {}
    function stopBuffering() {}
    function uncompressAllFiles() {}
    function unlinkArchive($archive) {}
    function webPhar($alias, $index, $f404, $mimetypes, $rewrites) {}
}
class PharData {
    function addEmptyDir($dirname) {}
    function addFromString($localname, $contents) {}
    function buildFromIterator($iter, $base_directory) {}
    function compress($compression, $extension) {}
    function compressFiles($compression) {}
    function __construct($fname, $flags) {}
    function convertToData($format, $compression, $extension) {}
    function convertToExecutable($format, $compression, $extension) {}
    function copy($oldfile, $newfile) {}
    function decompress($extension) {}
    function decompressFiles() {}
    function delMetadata() {}
    function delete($entry) {}
    function extractTo($pathto, $files, $overwrite) {}
    function isWritable() {}
    function offsetSet($offset, $value) {}
    function offsetUnset($offset) {}
    function setAlias($alias) {}
    function setDefaultStub($index, $webindex) {}
    function setStub($stub) {}
}
class PharFileInfo {
    function chmod($permissions) {}
    function compress($compression) {}
    function __construct($entry) {}
    function decompress() {}
    function delMetadata() {}
    function getCRC32() {}
    function getCompressedSize() {}
    function getMetaData() {}
    function getPharFlags() {}
    function hasMetadata() {}
    function isCRCChecked() {}
    function isCompressed() {}
    function isCompressedBZIP2() {}
    function isCompressedGZ() {}
    function setCompressedBZIP2() {}
    function setCompressedGZ() {}
    function setMetaData($metadata) {}
    function setUncompressed() {}
}
class Runkit_Sandbox_Parent {
    function __construct() {}
}
class SCA_LocalProxy {
    function createDataObject($type_namespace_uri, $type_name) {}
}
class SCA_SoapProxy {
    function createDataObject($type_namespace_uri, $type_name) {}
}
class SCA {
    function createDataObject($type_namespace_uri, $type_name) {}
    function getService($target, $binding, $config) {}
}
class SDO_DAS_ChangeSummary {
    const NONE = 0;
    const MODIFICATION = 0;
    const ADDITION = 0;
    const DELETION = 0;
    function beginLogging() {}
    function endLogging() {}
    function getChangeType($dataObject) {}
    function getChangedDataObjects() {}
    function getOldContainer($data_object) {}
    function getOldValues($data_object) {}
    function isLogging() {}
}
class SDO_DAS_DataFactory {
    function addPropertyToType($parent_type_namespace_uri, $parent_type_name, $property_name, $type_namespace_uri, $type_name, $options) {}
    function addType($type_namespace_uri, $type_name, $options) {}
    function getDataFactory() {}
}
class SDO_DAS_DataObject {
    function getChangeSummary() {}
}
class SDO_DAS_Setting {
    function getListIndex() {}
    function getPropertyIndex() {}
    function getPropertyName() {}
    function getValue() {}
}
class SDO_DataFactory {
    function create($type_namespace_uri, $type_name) {}
}
class SDO_DataObject {
    function clear() {}
    function createDataObject($identifier) {}
    function getContainer() {}
    function getSequence() {}
    function getTypeName() {}
    function getTypeNamespaceURI() {}
}
class SDO_Exception {
    function getCause() {}
}
class SDO_List {
    function insert($value, $index) {}
}
class SDO_Model_Property {
    function getContainingType() {}
    function getDefault() {}
    function getName() {}
    function getType() {}
    function isContainment() {}
    function isMany() {}
}
class SDO_Model_ReflectionDataObject {
    function __construct($data_object) {}
    function export($rdo, $return) {}
    function getContainmentProperty() {}
    function getInstanceProperties() {}
    function getType() {}
}
class SDO_Model_Type {
    function getBaseType() {}
    function getName() {}
    function getNamespaceURI() {}
    function getProperties() {}
    function getProperty($identifier) {}
    function isAbstractType() {}
    function isDataType() {}
    function isInstance($data_object) {}
    function isOpenType() {}
    function isSequencedType() {}
}
class SDO_Sequence {
    function getProperty($sequence_index) {}
    function insert($value, $sequenceIndex, $propertyIdentifier) {}
    function move($toIndex, $fromIndex) {}
}
class SDO_DAS_XML_Document {
    function getRootDataObject() {}
    function getRootElementName() {}
    function getRootElementURI() {}
    function setEncoding($encoding) {}
    function setXMLDeclaration($xmlDeclatation) {}
    function setXMLVersion($xmlVersion) {}
}
class SDO_DAS_XML {
    function addTypes($xsd_file) {}
    function create($xsd_file, $key) {}
    function createDataObject($namespace_uri, $type_name) {}
    function createDocument($document_element_name) {}
    function loadFile($xml_file) {}
    function loadString($xml_string) {}
    function saveFile($xdoc, $xml_file, $indent) {}
    function saveString($xdoc, $indent) {}
}
class SDO_DAS_Relational {
    function applyChanges($database_handle, $root_data_object) {}
    function __construct($database_metadata, $application_root_type, $SDO_containment_references_metadata) {}
    function createRootDataObject() {}
    function executePreparedQuery($database_handle, $prepared_statement, $value_list, $column_specifier) {}
    function executeQuery($database_handle, $SQL_statement, $column_specifier) {}
}
class SphinxClient {
    function addQuery($query, $index, $comment) {}
    function buildExcerpts($docs, $index, $words, $opts) {}
    function buildKeywords($query, $index, $hits) {}
    function __construct() {}
    function escapeString($string) {}
    function getLastError() {}
    function getLastWarning() {}
    function query($query, $index, $comment) {}
    function resetFilters() {}
    function resetGroupBy() {}
    function runQueries() {}
    function setArrayResult($array_result) {}
    function setConnectTimeout($timeout) {}
    function setFieldWeights($weights) {}
    function setFilter($attribute, $values, $exclude) {}
    function setFilterFloatRange($attribute, $min, $max, $exclude) {}
    function setFilterRange($attribute, $min, $max, $exclude) {}
    function setGeoAnchor($attrlat, $attrlong, $latitude, $longitude) {}
    function setGroupBy($attribute, $func, $groupsort) {}
    function setGroupDistinct($attribute) {}
    function setIDRange($min, $max) {}
    function setIndexWeights($weights) {}
    function setLimits($offset, $limit, $max, $cutoff) {}
    function setMatchMode($mode) {}
    function setMaxQueryTime($qtime) {}
    function setRankingMode($ranker) {}
    function setRetries($count, $delay) {}
    function setServer($server, $port) {}
    function setSortMode($mode, $sortby) {}
    function updateAttributes($index, $attributes, $values) {}
}
class ArrayIterator {
    function current() {}
    function key() {}
    function next() {}
    function rewind() {}
    function seek($position) {}
    function valid() {}
}
class ArrayObject {
    function append($newval) {}
    function count() {}
    function getIterator() {}
    function offsetExists($index) {}
    function offsetGet($index) {}
    function offsetSet($index, $newval) {}
    function offsetUnset($index) {}
}
class CachingIterator {
    const CALL_TOSTRING = 0;
    const CATCH_GET_CHILD = 0;
    function hasNext() {}
    function next() {}
    function rewind() {}
    function __toString() {}
    function valid() {}
}
class DirectoryIterator {
    function current() {}
    function getATime() {}
    function getCTime() {}
    function getFilename() {}
    function getGroup() {}
    function getInode() {}
    function getMTime() {}
    function getOwner() {}
    function getPath() {}
    function getPathname() {}
    function getPerms() {}
    function getSize() {}
    function getType() {}
    function isDir() {}
    function isDot() {}
    function isExecutable() {}
    function isFile() {}
    function isLink() {}
    function isReadable() {}
    function isWritable() {}
    function key() {}
    function next() {}
    function rewind() {}
    function valid() {}
}
class FilterIterator {
    function current() {}
    function getInnerIterator() {}
    function key() {}
    function next() {}
    function rewind() {}
    function valid() {}
}
class LimitIterator {
    function getPosition() {}
    function next() {}
    function rewind() {}
    function seek($position) {}
    function valid() {}
}
class ParentIterator {
    function getChildren() {}
    function hasChildren() {}
    function next() {}
    function rewind() {}
}
class RecursiveCachingIterator {
    function getChildren() {}
    function hasChildren() {}
}
class RecursiveDirectoryIterator {
    function getChildren() {}
    function hasChildren($allow_links) {}
    function key() {}
    function next() {}
    function rewind() {}
}
class RecursiveIteratorIterator {
    const LEAVES_ONLY = 0;
    const SELF_FIRST = 0;
    const CHILD_FIRST = 0;
    function current() {}
    function getDepth() {}
    function getSubIterator() {}
    function key() {}
    function next() {}
    function rewind() {}
    function valid() {}
}
class SimpleXMLIterator {
    function current() {}
    function getChildren() {}
    function hasChildren() {}
    function key() {}
    function next() {}
    function rewind() {}
    function valid() {}
}
class SplDoublyLinkedList {
    function bottom() {}
    function count() {}
    function current() {}
    function getIteratorMode() {}
    function isEmpty() {}
    function key() {}
    function next() {}
    function offsetExists($index) {}
    function offsetGet($index) {}
    function offsetSet($index, $newval) {}
    function offsetUnset($index) {}
    function pop() {}
    function push($value) {}
    function rewind() {}
    function setIteratorMode($mode) {}
    function shift() {}
    function top() {}
    function unshift($value) {}
    function valid() {}
}
class SplHeap {
    function compare($value1, $value2) {}
    function count() {}
    function current() {}
    function extract() {}
    function insert($value) {}
    function isEmpty() {}
    function key() {}
    function next() {}
    function recoverFromCorruption() {}
    function rewind() {}
    function top() {}
    function valid() {}
}
class SplMaxHeap {
    function compare($value1, $value2) {}
}
class SplMinHeap {
    function compare($value1, $value2) {}
}
class SplPriorityQueue {
    function compare($priority1, $priority1) {}
    function count() {}
    function current() {}
    function extract() {}
    function insert($value, $priority) {}
    function isEmpty() {}
    function key() {}
    function next() {}
    function recoverFromCorruption() {}
    function rewind() {}
    function setExtractFlags($flags) {}
    function top() {}
    function valid() {}
}
class SplQueue {
    function dequeue() {}
    function enqueue($value) {}
    function setIteratorMode($mode) {}
}
class SplStack {
    function setIteratorMode($mode) {}
}
class SQLite3 {
    function changes() {}
    function close() {}
    function __construct($filename, $flags, $encryption_key) {}
    function createAggregate($name, $step_callback, $final_callback, $argument_count) {}
    function createFunction($name, $callback, $argument_count) {}
    function escapeString($value) {}
    function exec($query) {}
    function lastErrorCode() {}
    function lastErrorMsg() {}
    function lastInsertRowID() {}
    function loadExtension($shared_library) {}
    function open($filename, $flags, $encryption_key) {}
    function prepare($query) {}
    function query($query) {}
    function querySingle($query, $entire_row) {}
    function version() {}
}
class SQLite3_result {
    function columnName($column_number) {}
    function columnType($column_number) {}
    function fetchArray($mode) {}
    function finalize() {}
    function numColumns() {}
    function reset() {}
}
class SQLite3_stmt {
    function bindParam($param_number, $param, $type) {}
    function bindValue($param_number, $param, $type) {}
    function clear() {}
    function close() {}
    function execute() {}
    function paramCount() {}
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
    function __construct($index_names) {}
}
class tidy {
    function __construct($filename, $config, $encoding, $use_include_path) {}
}
class tidy_node {
    function get_attr($attrib_id) {}
    function get_nodes($node_id) {}
    function next() {}
    function prev() {}
}
class tidyNode {
    function hasChildren() {}
    function hasSiblings() {}
    function isAsp() {}
    function isComment() {}
    function isHtml() {}
    function isJste() {}
    function isPhp() {}
    function isText() {}
    function getParent() {}
}
class XMLReader {
    function close() {}
    function expand() {}
    function getAttribute($name) {}
    function getAttributeNo($index) {}
    function getAttributeNs($localName, $namespaceURI) {}
    function getParserProperty($property) {}
    function isValid() {}
    function lookupNamespace($prefix) {}
    function moveToAttribute($name) {}
    function moveToAttributeNo($index) {}
    function moveToAttributeNs($localName, $namespaceURI) {}
    function moveToElement() {}
    function moveToFirstAttribute() {}
    function moveToNextAttribute() {}
    function next($localname) {}
    function open($URI, $encoding, $options) {}
    function read() {}
    function readInnerXML() {}
    function readOuterXML() {}
    function readString() {}
    function setParserProperty($property, $value) {}
    function setRelaxNGSchema($filename) {}
    function setRelaxNGSchemaSource($source) {}
    function setSchema($filename) {}
    function xml($source, $encoding, $options) {}
}
class ZipArchive {
    function addEmptyDir($dirname) {}
    function addFile($filename, $localname) {}
    function addFromString($localname, $contents) {}
    function close() {}
    function deleteIndex($index) {}
    function deleteName($name) {}
    function extractTo($destination, $entries) {}
    function getArchiveComment() {}
    function getCommentIndex($index, $flags) {}
    function getCommentName($name, $flags) {}
    function getFromIndex($index, $flags) {}
    function getFromName($name, $flags) {}
    function getNameIndex($index) {}
    function getStream($name) {}
    function locateName($name, $flags) {}
    function open($filename, $flags) {}
    function renameIndex($index, $newname) {}
    function renameName($name, $newname) {}
    function setArchiveComment($comment) {}
    function setCommentIndex($index, $comment) {}
    function setCommentName($name, $comment) {}
    function statIndex($index, $flags) {}
    function statName($name, $flags) {}
    function unchangeAll() {}
    function unchangeArchive() {}
    function unchangeIndex($index) {}
    function unchangeName($name) {}
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
define('__COMPILER_HALT_OFFSET__', 0);
define('EXTR_OVERWRITE', 0);
define('EXTR_SKIP', 0);
define('EXTR_PREFIX_SAME', 0);
define('EXTR_PREFIX_ALL', 0);
define('EXTR_PREFIX_INVALID', 0);
define('EXTR_PREFIX_IF_EXISTS', 0);
define('EXTR_IF_EXISTS', 0);
define('SORT_ASC', 0);
define('SORT_DESC', 0);
define('SORT_REGULAR', 0);
define('SORT_NUMERIC', 0);
define('SORT_STRING', 0);
define('CASE_LOWER', 0);
define('CASE_UPPER', 0);
define('COUNT_NORMAL', 0);
define('COUNT_RECURSIVE', 0);
define('ASSERT_ACTIVE', 0);
define('ASSERT_CALLBACK', 0);
define('ASSERT_BAIL', 0);
define('ASSERT_WARNING', 0);
define('ASSERT_QUIET_EVAL', 0);
define('CONNECTION_ABORTED', 0);
define('CONNECTION_NORMAL', 0);
define('CONNECTION_TIMEOUT', 0);
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
define('CRYPT_SALT_LENGTH', 0);
define('CRYPT_STD_DES', 0);
define('CRYPT_EXT_DES', 0);
define('CRYPT_MD5', 0);
define('CRYPT_BLOWFISH', 0);
define('DIRECTORY_SEPARATOR', '');
define('SEEK_SET', 0);
define('SEEK_CUR', 0);
define('SEEK_END', 0);
define('LOCK_SH', 0);
define('LOCK_EX', 0);
define('LOCK_UN', 0);
define('LOCK_NB', 0);
define('HTML_SPECIALCHARS', 0);
define('HTML_ENTITIES', 0);
define('ENT_COMPAT', 0);
define('ENT_QUOTES', 0);
define('ENT_NOQUOTES', 0);
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
define('STR_PAD_LEFT', 0);
define('STR_PAD_RIGHT', 0);
define('STR_PAD_BOTH', 0);
define('PATHINFO_DIRNAME', 0);
define('PATHINFO_BASENAME', 0);
define('PATHINFO_EXTENSION', 0);
define('PATH_SEPARATOR', '');
define('CHAR_MAX', 0);
define('LC_CTYPE', 0);
define('LC_NUMERIC', 0);
define('LC_TIME', 0);
define('LC_COLLATE', 0);
define('LC_MONETARY', 0);
define('LC_ALL', 0);
define('LC_MESSAGES', 0);
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
