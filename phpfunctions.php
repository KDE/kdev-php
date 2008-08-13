<?php
function ovrimos_prepare($connection_id, $query) {}
function ovrimos_execute($result_id, $parameters_array) {}
function ovrimos_fetch_into($result_id, $result_array, $how, $rownumber) {}
function ovrimos_field_num($result_id, $field_name) {}
function ovrimos_free_result($result_id) {}
function ovrimos_exec($connection_id, $query) {}
function ovrimos_longreadlen($result_id, $length) {}
function ovrimos_num_rows($result_id) {}
function ovrimos_cursor($result_id) {}
function ovrimos_field_name($result_id, $field_number) {}
function ovrimos_num_fields($result_id) {}
function ovrimos_commit($connection_id) {}
function ovrimos_rollback($connection_id) {}
function ovrimos_field_type($result_id, $field_number) {}
function ovrimos_result_all($result_id, $format) {}
function ovrimos_fetch_row($result_id, $how, $row_number) {}
function ovrimos_connect($host, $dborport, $user, $password) {}
function ovrimos_field_len($result_id, $field_number) {}
function ovrimos_result($result_id, $field) {}
function ovrimos_close($connection) {}
function filepro_fieldname($field_number) {}
function filepro_retrieve($row_number, $field_number) {}
function filepro_fieldwidth($field_number) {}
function filepro_fieldtype($field_number) {}
function filepro_rowcount() {}
function filepro_fieldcount() {}
function filepro($directory) {}
function newt_form_get_current($form) {}
function newt_scale($left, $top, $width, $full_value) {}
function newt_grid_set_field($grid, $col, $row, $type, $val, $pad_left, $pad_top, $pad_right, $pad_bottom, $anchor, $flags) {}
function newt_resume() {}
function newt_open_window($left, $top, $width, $height, $title) {}
function newt_checkbox_tree_set_entry_value($checkboxtree, $data, $value) {}
function newt_finished() {}
function newt_draw_root_text($left, $top, $text) {}
function newt_listitem_get_data($item) {}
function newt_textbox_reflowed($left, $top, $text, $width, $flex_down, $flex_up, $flags) {}
function newt_delay($microseconds) {}
function newt_checkbox_tree_get_selection($checkboxtree) {}
function newt_form_set_background($from, $background) {}
function newt_set_help_callback($function) {}
function newt_component_add_callback($component, $func_name, $data) {}
function newt_clear_key_buffer() {}
function newt_win_ternary($title, $button1_text, $button2_text, $button3_text, $format, $args) {}
function newt_component_takes_focus($component, $takes_focus) {}
function newt_form_set_width($form, $width) {}
function newt_button($left, $top, $text) {}
function newt_checkbox_tree_set_current($checkboxtree, $data) {}
function newt_win_messagev($title, $button_text, $format, $args) {}
function newt_grid_free($grid, $recurse) {}
function newt_entry_get_value($entry) {}
function newt_form_set_timer($form, $milliseconds) {}
function newt_listbox_item_count($listbox) {}
function newt_checkbox_tree($left, $top, $height, $flags) {}
function newt_grid_basic_window($text, $middle, $buttons) {}
function newt_entry_set_flags($entry, $flags, $sense) {}
function newt_textbox($left, $top, $width, $height, $flags) {}
function newt_reflow_text($text, $width, $flex_down, $flex_up, $actual_width, $actual_height) {}
function newt_listbox_set_current_by_key($listbox, $key) {}
function newt_listbox_select_item($listbox, $key, $sense) {}
function newt_checkbox_get_value($checkbox) {}
function newt_listbox_clear($listobx) {}
function newt_checkbox_set_flags($checkbox, $flags, $sense) {}
function newt_checkbox_tree_set_entry($checkboxtree, $data, $text) {}
function newt_label_set_text($label, $text) {}
function newt_entry($left, $top, $width, $init_value, $flags) {}
function newt_grid_wrapped_window_at($grid, $title, $left, $top) {}
function newt_grid_h_close_stacked($element1_type, $element1) {}
function newt_centered_window($width, $height, $title) {}
function newt_bell() {}
function newt_init() {}
function newt_listbox($left, $top, $height, $flags) {}
function newt_win_entries($title, $text, $suggested_width, $flex_down, $flex_up, $data_width, $items, $button1) {}
function newt_set_suspend_callback($function, $data) {}
function newt_listbox_get_selection($listbox) {}
function newt_grid_place($grid, $left, $top) {}
function newt_form_add_hot_key($form, $key) {}
function newt_form_add_components($form, $components) {}
function newt_win_message($title, $button_text, $format, $args) {}
function newt_grid_add_components_to_form($grid, $form, $recurse) {}
function newt_get_screen_size($cols, $rows) {}
function newt_grid_simple_window($text, $middle, $buttons) {}
function newt_button_bar($buttons) {}
function newt_win_choice($title, $button1_text, $button2_text, $format, $args) {}
function newt_draw_form($form) {}
function newt_listbox_set_current($listbox, $num) {}
function newt_radio_get_current($set_member) {}
function newt_grid_h_stacked($element1_type, $element1) {}
function newt_cls() {}
function newt_checkbox_tree_multi($left, $top, $height, $seq, $flags) {}
function newt_pop_window() {}
function newt_win_menu($title, $text, $suggestedWidth, $flexDown, $flexUp, $maxListHeight, $items, $listItem, $button1) {}
function newt_redraw_help_line() {}
function newt_checkbox_tree_add_item($checkboxtree, $text, $data, $flags, $index) {}
function newt_create_grid($cols, $rows) {}
function newt_listbox_set_width($listbox, $width) {}
function newt_listbox_get_current($listbox) {}
function newt_pop_help_line() {}
function newt_listbox_delete_entry($listbox, $key) {}
function newt_label($left, $top, $text) {}
function newt_radiobutton($left, $top, $text, $is_default, $prev_button) {}
function newt_checkbox_tree_get_entry_value($checkboxtree, $data) {}
function newt_listbox_append_entry($listbox, $text, $data) {}
function newt_entry_set($entry, $value, $cursor_at_end) {}
function newt_form_watch_fd($form, $stream, $flags) {}
function newt_listbox_clear_selection($listbox) {}
function newt_grid_wrapped_window($grid, $title) {}
function newt_grid_get_size($grid, $width, $height) {}
function newt_textbox_set_text($textbox, $text) {}
function newt_listbox_insert_entry($listbox, $text, $data, $key) {}
function newt_run_form($form) {}
function newt_form_run($form, $exit_struct) {}
function newt_refresh() {}
function newt_scrollbar_set($scrollbar, $where, $total) {}
function newt_form_add_component($form, $component) {}
function newt_textbox_get_num_lines($textbox) {}
function newt_checkbox_set_value($checkbox, $value) {}
function newt_form_set_size($form) {}
function newt_vertical_scrollbar($left, $top, $height, $normal_colorset, $thumb_colorset) {}
function newt_checkbox_tree_get_current($checkboxtree) {}
function newt_compact_button($left, $top, $text) {}
function newt_push_help_line($text) {}
function newt_listbox_set_entry($listbox, $num, $text) {}
function newt_form_destroy($form) {}
function newt_checkbox_tree_set_width($checkbox_tree, $width) {}
function newt_form_set_height($form, $height) {}
function newt_form($vert_bar, $help, $flags) {}
function newt_checkbox_tree_find_item($checkboxtree, $data) {}
function newt_cursor_off() {}
function newt_entry_set_filter($entry, $filter, $data) {}
function newt_wait_for_key() {}
function newt_suspend() {}
function newt_textbox_set_height($textbox, $height) {}
function newt_listbox_set_data($listbox, $num, $data) {}
function newt_grid_v_close_stacked($element1_type, $element1) {}
function newt_checkbox($left, $top, $text, $def_value, $seq) {}
function newt_resize_screen($redraw) {}
function newt_listitem($left, $top, $text, $is_default, $prev_item, $data, $flags) {}
function newt_checkbox_tree_get_multi_selection($checkboxtree, $seqnum) {}
function newt_cursor_on() {}
function newt_scale_set($scale, $amount) {}
function newt_grid_v_stacked($element1_type, $element1) {}
function newt_listitem_set($item, $text) {}
function variant_neg($variant) {}
function variant_cmp($left, $right, $lcid, $flags) {}
function com_release() {}
function com_print_typeinfo($comobject, $dispinterface, $wantsink) {}
function variant_imp($left, $right) {}
function variant_add($left, $right) {}
function com_isenum($com_module) {}
function variant_cast($variant, $type) {}
function variant_eqv($left, $right) {}
function variant_fix($variant) {}
function com_create_guid() {}
function variant_set($variant, $value) {}
function variant_mod($left, $right) {}
function variant_round($variant, $decimals) {}
function com_load_typelib($typelib_name, $case_insensitive) {}
function variant_xor($left, $right) {}
function variant_date_to_timestamp($variant) {}
function variant_abs($val) {}
function variant_sub($left, $right) {}
function variant_cat($left, $right) {}
function variant_and($left, $right) {}
function variant_int($variant) {}
function com_message_pump($timeoutms) {}
function variant_or($left, $right) {}
function variant_div($left, $right) {}
function variant_pow($left, $right) {}
function com_invoke($com_object, $function_name, $function_parameters) {}
function variant_mul($left, $right) {}
function variant_date_from_timestamp($timestamp) {}
function com_addref() {}
function variant_get_type($variant) {}
function variant_set_type($variant, $type) {}
function variant_not($variant) {}
function variant_idiv($left, $right) {}
function com_event_sink($comobject, $sinkobject, $sinkinterface) {}
function com_get_active_object($progid, $code_page) {}
function ming_useswfversion($version) {}
function ming_setcubicthreshold($threshold) {}
function ming_setswfcompression($level) {}
function ming_keypress($char) {}
function ming_setscale($scale) {}
function ming_useconstants($use) {}
function session_pgsql_get_field() {}
function session_pgsql_status() {}
function session_pgsql_add_error($error_level, $error_message) {}
function session_pgsql_get_error($with_error_message) {}
function session_pgsql_set_field($value) {}
function session_pgsql_reset() {}
function enchant_broker_describe($broker) {}
function enchant_broker_free($broker) {}
function enchant_dict_add_to_session($dict, $word) {}
function enchant_broker_init() {}
function enchant_broker_request_dict($broker, $tag) {}
function enchant_dict_suggest($dict, $word) {}
function enchant_broker_request_pwl_dict($broker, $filename) {}
function enchant_broker_list_dicts($broker) {}
function enchant_broker_set_ordering($broker, $tag, $ordering) {}
function enchant_dict_is_in_session($dict, $word) {}
function enchant_dict_add_to_personal($dict, $word) {}
function enchant_dict_quick_check($dict, $word, $suggestions) {}
function enchant_dict_check($dict, $word) {}
function enchant_dict_describe($dict) {}
function enchant_broker_get_error($broker) {}
function enchant_dict_get_error($dict) {}
function enchant_broker_free_dict($dict) {}
function enchant_broker_dict_exists($broker, $tag) {}
function enchant_dict_store_replacement($dict, $mis, $cor) {}
function fdf_set_value($fdf_document, $fieldname, $value, $isName) {}
function fdf_get_opt($fdf_document, $fieldname, $element) {}
function fdf_get_flags($fdf_document, $fieldname, $whichflags) {}
function fdf_set_javascript_action($fdf_document, $fieldname, $trigger, $script) {}
function fdf_set_ap($fdf_document, $field_name, $face, $filename, $page_number) {}
function fdf_get_file($fdf_document) {}
function fdf_add_template($fdf_document, $newpage, $filename, $template, $rename) {}
function fdf_get_attachment($fdf_document, $fieldname, $savepath) {}
function fdf_open_string($fdf_data) {}
function fdf_header() {}
function fdf_get_status($fdf_document) {}
function fdf_add_doc_javascript($fdf_document, $script_name, $script_code) {}
function fdf_enum_values($fdf_document, $function, $userdata) {}
function fdf_set_submit_form_action($fdf_document, $fieldname, $trigger, $script, $flags) {}
function fdf_set_encoding($fdf_document, $encoding) {}
function fdf_save_string($fdf_document) {}
function fdf_remove_item($fdf_document, $fieldname, $item) {}
function fdf_set_file($fdf_document, $url, $target_frame) {}
function fdf_get_value($fdf_document, $fieldname, $which) {}
function fdf_create() {}
function fdf_set_flags($fdf_document, $fieldname, $whichFlags, $newFlags) {}
function fdf_get_ap($fdf_document, $field, $face, $filename) {}
function fdf_next_field_name($fdf_document, $fieldname) {}
function fdf_errno() {}
function fdf_open($filename) {}
function fdf_set_opt($fdf_document, $fieldname, $element, $str1, $str2) {}
function fdf_get_version($fdf_document) {}
function fdf_set_status($fdf_document, $status) {}
function fdf_save($fdf_document, $filename) {}
function fdf_error($error_code) {}
function fdf_set_target_frame($fdf_document, $frame_name) {}
function fdf_close($fdf_document) {}
function fdf_set_version($fdf_document, $version) {}
function fdf_get_encoding($fdf_document) {}
function fdf_set_on_import_javascript($fdf_document, $script, $before_data_import) {}
function pg_field_is_null($result, $row, $field) {}
function pg_lo_create($connection, $object_id) {}
function pg_lo_close($large_object) {}
function pg_ping($connection) {}
function pg_dbname($connection) {}
function pg_lo_seek($large_object, $offset, $whence) {}
function pg_copy_from($connection, $table_name, $rows, $delimiter, $null_as) {}
function pg_connection_reset($connection) {}
function pg_select($connection, $table_name, $assoc_array, $options) {}
function pg_last_notice($connection) {}
function pg_update($connection, $table_name, $data, $condition, $options) {}
function pg_result_seek($result, $offset) {}
function pg_get_notify($connection, $result_type) {}
function pg_lo_read($large_object, $len) {}
function pg_prepare($connection, $stmtname, $query) {}
function pg_fetch_array($result, $row, $result_type) {}
function pg_fetch_row($result, $row) {}
function pg_send_query($connection, $query) {}
function pg_lo_unlink($connection, $oid) {}
function pg_field_table($result, $field_number, $oid_only) {}
function pg_fetch_all_columns($result, $column) {}
function pg_pconnect($connection_string, $connect_type) {}
function pg_options($connection) {}
function pg_version($connection) {}
function pg_lo_read_all($large_object) {}
function pg_put_line($data) {}
function pg_execute($connection, $stmtname, $params) {}
function pg_fetch_all($result) {}
function pg_fetch_object($result, $row, $result_type) {}
function pg_lo_import($connection, $pathname, $object_id) {}
function pg_result_error_field($result, $fieldcode) {}
function pg_trace($pathname, $mode, $connection) {}
function pg_client_encoding($connection) {}
function pg_convert($connection, $table_name, $assoc_array, $options) {}
function pg_field_type($result, $field_number) {}
function pg_set_error_verbosity($connection, $verbosity) {}
function pg_result_status($result, $type) {}
function pg_query_params($connection, $query, $params) {}
function pg_fetch_assoc($result, $row) {}
function pg_last_error($connection) {}
function pg_lo_export($connection, $oid, $pathname) {}
function pg_cancel_query($connection) {}
function pg_fetch_result($result, $row, $field) {}
function pg_delete($connection, $table_name, $assoc_array, $options) {}
function pg_free_result($result) {}
function pg_copy_to($connection, $table_name, $delimiter, $null_as) {}
function pg_transaction_status($connection) {}
function pg_end_copy($connection) {}
function pg_get_pid($connection) {}
function pg_query($query) {}
function pg_escape_string($connection, $data) {}
function pg_num_fields($result) {}
function pg_insert($connection, $table_name, $assoc_array, $options) {}
function pg_port($connection) {}
function pg_field_num($result, $field_name) {}
function pg_host($connection) {}
function pg_untrace($connection) {}
function pg_escape_bytea($connection, $data) {}
function pg_tty($connection) {}
function pg_field_name($result, $field_number) {}
function pg_field_prtlen($result, $row_number, $field_name_or_number) {}
function pg_lo_open($connection, $oid, $mode) {}
function pg_set_client_encoding($encoding) {}
function pg_meta_data($connection, $table_name) {}
function pg_connect($connection_string, $connect_type) {}
function pg_send_prepare($connection, $stmtname, $query) {}
function pg_close($connection) {}
function pg_lo_write($large_object, $data, $len) {}
function pg_num_rows($result) {}
function pg_lo_tell($large_object) {}
function pg_connection_busy($connection) {}
function pg_field_size($result, $field_number) {}
function pg_parameter_status($connection, $param_name) {}
function pg_send_execute($connection, $stmtname, $params) {}
function pg_unescape_bytea($data) {}
function pg_get_result($connection) {}
function pg_send_query_params($connection, $query, $params) {}
function pg_connection_status($connection) {}
function pg_result_error($result) {}
function pg_field_type_oid($result, $field_number) {}
function pg_affected_rows($result) {}
function pg_last_oid($result) {}
function locale_get_default() {}
function locale_set_default($name) {}
function imagefttext($image, $size, $angle, $x, $y, $color, $fontfile, $text, $extrainfo) {}
function imageloadfont($file) {}
function imagexbm($image, $filename, $foreground) {}
function imagefilledellipse($image, $cx, $cy, $width, $height, $color) {}
function imagesetbrush($image, $brush) {}
function iptcparse($iptcblock) {}
function imagefontwidth($font) {}
function imagepsslantfont($font_index, $slant) {}
function gd_info() {}
function imagegammacorrect($image, $inputgamma, $outputgamma) {}
function imagecolormatch($image1, $image2) {}
function imagecreate($width, $height) {}
function imageline($image, $x1, $y1, $x2, $y2, $color) {}
function imagefilledpolygon($image, $points, $num_points, $color) {}
function imagecolorexactalpha($image, $red, $green, $blue, $alpha) {}
function imagecreatefromwbmp($filename) {}
function imagecreatefromgd($filename) {}
function imagepsloadfont($filename) {}
function imagesetstyle($image, $style) {}
function imagefill($image, $x, $y, $color) {}
function imagecolordeallocate($image, $color) {}
function imagepsencodefont($font_index, $encodingfile) {}
function imagegd2($image, $filename, $chunk_size, $type) {}
function imagecolorresolvealpha($image, $red, $green, $blue, $alpha) {}
function getimagesize($filename, $imageinfo) {}
function image_type_to_extension($imagetype, $include_dot) {}
function imagerectangle($image, $x1, $y1, $x2, $y2, $color) {}
function imagecharup($image, $font, $x, $y, $c, $color) {}
function imageantialias($image, $on) {}
function imagecolorresolve($image, $red, $green, $blue) {}
function imagecolorclosest($image, $red, $green, $blue) {}
function imagelayereffect($image, $effect) {}
function imagefontheight($font) {}
function imagecreatefromxbm($filename) {}
function imagecopy($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h) {}
function imagecreatefromgd2($filename) {}
function imagecolorsforindex($image, $index) {}
function image2wbmp($image, $filename, $threshold) {}
function imagesx($image) {}
function image_type_to_mime_type($imagetype) {}
function imagegrabwindow($window, $client_area) {}
function imagecreatefromxpm($filename) {}
function imagepsfreefont($font_index) {}
function imageftbbox($size, $angle, $fontfile, $text, $extrainfo) {}
function png2wbmp($pngname, $wbmpname, $dest_height, $dest_width, $threshold) {}
function imagepsextendfont($font_index, $extend) {}
function imagecopymerge($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h, $pct) {}
function imagerotate($image, $angle, $bgd_color, $ignore_transparent) {}
function imagesetthickness($image, $thickness) {}
function imagearc($image, $cx, $cy, $width, $height, $start, $end, $color) {}
function imagesy($image) {}
function imagecolorallocate($image, $red, $green, $blue) {}
function imagecolorexact($image, $red, $green, $blue) {}
function imagesettile($image, $tile) {}
function imageistruecolor($image) {}
function imagecopymergegray($dst_im, $src_im, $dst_x, $dst_y, $src_x, $src_y, $src_w, $src_h, $pct) {}
function imageinterlace($image, $interlace) {}
function imagefilledrectangle($image, $x1, $y1, $x2, $y2, $color) {}
function imagestring($image, $font, $x, $y, $string, $color) {}
function imagecreatefromjpeg($filename) {}
function imagegrabscreen() {}
function imagesetpixel($image, $x, $y, $color) {}
function imagecreatefromstring($data) {}
function imagecolorclosesthwb($image, $red, $green, $blue) {}
function imagecolorallocatealpha($image, $red, $green, $blue, $alpha) {}
function imageconvolution($image, $matrix, $div, $offset) {}
function imagepsbbox($text, $font, $size) {}
function imagecolorset($image, $index, $red, $green, $blue) {}
function imagecreatefrompng($filename) {}
function imagedashedline($image, $x1, $y1, $x2, $y2, $color) {}
function imagecopyresampled($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h) {}
function imagegif($image, $filename) {}
function imagepolygon($image, $points, $num_points, $color) {}
function imagealphablending($image, $blendmode) {}
function imagettfbbox($size, $angle, $fontfile, $text) {}
function imagetruecolortopalette($image, $dither, $ncolors) {}
function iptcembed($iptcdata, $jpeg_file_name, $spool) {}
function imagedestroy($image) {}
function imagecopyresized($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h) {}
function imagechar($image, $font, $x, $y, $c, $color) {}
function imagecreatefromgif($filename) {}
function imagecolorclosestalpha($image, $red, $green, $blue, $alpha) {}
function imagecreatefromgd2part($filename, $srcX, $srcY, $width, $height) {}
function imageellipse($image, $cx, $cy, $width, $height, $color) {}
function imagefilter($image, $filtertype, $arg1, $arg2, $arg3, $arg4) {}
function imagecolorat($image, $x, $y) {}
function imagesavealpha($image, $saveflag) {}
function imagecolortransparent($image, $color) {}
function imagepalettecopy($destination, $source) {}
function imagecreatetruecolor($width, $height) {}
function imagefilltoborder($image, $x, $y, $border, $color) {}
function imagettftext($image, $size, $angle, $x, $y, $color, $fontfile, $text) {}
function imagejpeg($image, $filename, $quality) {}
function imagepng($image, $filename, $quality, $filters) {}
function imagefilledarc($image, $cx, $cy, $width, $height, $start, $end, $color, $style) {}
function imagepstext($image, $text, $font_index, $size, $foreground, $background, $x, $y, $space, $tightness, $angle, $antialias_steps) {}
function imagewbmp($image, $filename, $foreground) {}
function imagestringup($image, $font, $x, $y, $string, $color) {}
function imagetypes() {}
function jpeg2wbmp($jpegname, $wbmpname, $dest_height, $dest_width, $threshold) {}
function imagecolorstotal($image) {}
function imagegd($image, $filename) {}
function filter_list() {}
function filter_input($type, $variable_name, $filter, $options) {}
function filter_var($variable, $filter, $options) {}
function filter_id($filtername) {}
function filter_var_array($data, $definition) {}
function filter_input_array($type, $definition) {}
function filter_has_var($type, $variable_name) {}
function memcache_debug($on_off) {}
function gzeof($zp) {}
function gzinflate($data, $length) {}
function gzseek($zp, $offset) {}
function gzclose($zp) {}
function gztell($zp) {}
function gzfile($filename, $use_include_path) {}
function gzread($zp, $length) {}
function zlib_get_coding_type() {}
function gzcompress($data, $level) {}
function gzrewind($zp) {}
function gzopen($filename, $mode, $use_include_path) {}
function gzgetss($zp, $length, $allowable_tags) {}
function gzuncompress($data, $length) {}
function gzdeflate($data, $level) {}
function gzpassthru($zp) {}
function readgzfile($filename, $use_include_path) {}
function gzwrite($zp, $string, $length) {}
function gzgetc($zp) {}
function gzgets($zp, $length) {}
function gzdecode($data, $length) {}
function gzencode($data, $level, $encoding_mode) {}
function bcompiler_write_class($filehandle, $className, $extends) {}
function bcompiler_write_function($filehandle, $functionName) {}
function bcompiler_load_exe($filename) {}
function bcompiler_read($filehandle) {}
function bcompiler_parse_class($class, $callback) {}
function bcompiler_write_file($filehandle, $filename) {}
function bcompiler_write_included_filename($filehandle, $filename) {}
function bcompiler_write_header($filehandle, $write_ver) {}
function bcompiler_write_constant($filehandle, $constantName) {}
function bcompiler_write_exe_footer($filehandle, $startpos) {}
function bcompiler_write_footer($filehandle) {}
function bcompiler_load($filename) {}
function bcompiler_write_functions_from_file($filehandle, $fileName) {}
function shm_get_var($shm_identifier, $variable_key) {}
function shm_put_var($shm_identifier, $variable_key, $variable) {}
function msg_stat_queue($queue) {}
function sem_remove($sem_identifier) {}
function msg_queue_exists($key) {}
function shm_remove($shm_identifier) {}
function shm_attach($key, $memsize, $perm) {}
function sem_release($sem_identifier) {}
function sem_get($key, $max_acquire, $perm, $auto_release) {}
function shm_remove_var($shm_identifier, $variable_key) {}
function msg_receive($queue, $desiredmsgtype, $msgtype, $maxsize, $message, $unserialize, $flags, $errorcode) {}
function ftok($pathname, $proj) {}
function msg_get_queue($key, $perms) {}
function msg_remove_queue($queue) {}
function sem_acquire($sem_identifier) {}
function msg_send($queue, $msgtype, $message, $serialize, $blocking, $errorcode) {}
function msg_set_queue($queue, $data) {}
function shm_detach($shm_identifier) {}
function crack_check($dictionary, $password) {}
function crack_opendict($dictionary) {}
function crack_closedict($dictionary) {}
function crack_getlastmessage() {}
function posix_getgrgid($gid) {}
function posix_getgrnam($name) {}
function posix_getpwuid($uid) {}
function posix_strerror($errno) {}
function posix_initgroups($name, $base_group_id) {}
function posix_getpgid($pid) {}
function posix_getuid() {}
function posix_setegid($gid) {}
function posix_getsid($pid) {}
function posix_mknod($pathname, $mode, $major, $minor) {}
function posix_isatty($fd) {}
function posix_getpid() {}
function posix_ttyname($fd) {}
function posix_getgid() {}
function posix_uname() {}
function posix_setpgid($pid, $pgid) {}
function posix_setgid($gid) {}
function posix_getrlimit() {}
function posix_getpgrp() {}
function posix_seteuid($uid) {}
function posix_setuid($uid) {}
function posix_getpwnam($username) {}
function posix_getcwd() {}
function posix_getlogin() {}
function posix_getppid() {}
function posix_getegid() {}
function posix_ctermid() {}
function posix_setsid() {}
function posix_times() {}
function posix_geteuid() {}
function posix_kill($pid, $sig) {}
function posix_get_last_error() {}
function posix_getgroups() {}
function posix_mkfifo($pathname, $mode) {}
function posix_access($file, $mode) {}
function snmp_set_enum_print($enum_print) {}
function snmpwalk($hostname, $community, $object_id, $timeout, $retries) {}
function snmpgetnext($host, $community, $object_id, $timeout, $retries) {}
function snmpwalkoid($hostname, $community, $object_id, $timeout, $retries) {}
function snmpget($hostname, $community, $object_id, $timeout, $retries) {}
function snmp_set_valueretrieval($method) {}
function snmp_set_quick_print($quick_print) {}
function snmpset($hostname, $community, $object_id, $type, $value, $timeout, $retries) {}
function snmp_get_quick_print() {}
function snmp_set_oid_numeric_print($oid_numeric_print) {}
function snmprealwalk($host, $community, $object_id, $timeout, $retries) {}
function snmp_set_oid_output_format($oid_format) {}
function snmp_read_mib($filename) {}
function snmp_get_valueretrieval() {}
function bbcode_destroy($bbcode_container) {}
function bbcode_add_element($bbcode_container, $tag_name, $tag_rules) {}
function bbcode_set_flags($bbcode_container, $flags, $mode) {}
function bbcode_add_smiley($bbcode_container, $smiley, $replace_by) {}
function bbcode_set_arg_parser($bbcode_container, $bbcode_arg_parser) {}
function bbcode_create($bbcode_initial_tags) {}
function bbcode_parse($bbcode_container, $to_parse) {}
function highlight_file($filename, $return) {}
function connection_aborted() {}
function uniqid($prefix, $more_entropy) {}
function connection_status() {}
function connection_timeout() {}
function time_sleep_until($timestamp) {}
function ignore_user_abort($setting) {}
function php_strip_whitespace($filename) {}
function php_check_syntax($filename, $error_message) {}
function sys_getloadavg() {}
function define($name, $value, $case_insensitive) {}
function unpack($format, $data) {}
function sleep($seconds) {}
function time_nanosleep($seconds, $nanoseconds) {}
function get_browser($user_agent, $return_array) {}
function usleep($micro_seconds) {}
function highlight_string($str, $return) {}
function pack($format, $args) {}
function constant($name) {}
function defined($name) {}
function geoip_org_by_name($hostname) {}
function geoip_record_by_name($hostname) {}
function geoip_region_by_name($hostname) {}
function geoip_db_filename($database) {}
function geoip_country_code3_by_name($hostname) {}
function geoip_country_name_by_name($hostname) {}
function geoip_id_by_name($hostname) {}
function geoip_country_code_by_name($hostname) {}
function geoip_isp_by_name($hostname) {}
function geoip_db_avail($database) {}
function geoip_database_info($database) {}
function geoip_db_get_all_info() {}
function readline_read_history($filename) {}
function readline_on_new_line() {}
function readline_callback_handler_remove() {}
function readline_callback_read_char() {}
function readline_info($varname, $newvalue) {}
function readline_completion_function($function) {}
function readline($prompt) {}
function readline_add_history($line) {}
function readline_redisplay() {}
function readline_list_history() {}
function readline_callback_handler_install($prompt, $callback) {}
function readline_clear_history() {}
function readline_write_history($filename) {}
function escapeshellcmd($command) {}
function proc_get_status($process) {}
function exec($command, $output, $return_var) {}
function proc_nice($increment) {}
function passthru($command, $return_var) {}
function proc_close($process) {}
function proc_terminate($process, $signal) {}
function shell_exec($cmd) {}
function system($command, $return_var) {}
function proc_open($cmd, $descriptorspec, $pipes, $cwd, $env, $other_options) {}
function escapeshellarg($arg) {}
function svn_fs_file_length($fsroot, $path) {}
function svn_cat($repos_url, $revision_no) {}
function svn_fs_make_file($root, $path) {}
function svn_fs_txn_root($txn) {}
function svn_fs_copy($from_root, $from_path, $to_root, $to_path) {}
function svn_fs_file_contents($fsroot, $path) {}
function svn_repos_create($path, $config, $fsconfig) {}
function svn_fs_revision_prop($fs, $revnum, $propname) {}
function svn_fs_delete($root, $path) {}
function svn_repos_open($path) {}
function svn_repos_recover($path) {}
function svn_fs_apply_text($root, $path) {}
function svn_add($path, $recursive, $force) {}
function svn_fs_check_path($fsroot, $path) {}
function svn_fs_is_file($root, $path) {}
function svn_fs_is_dir($root, $path) {}
function svn_status($path, $flags) {}
function svn_fs_youngest_rev($fs) {}
function svn_fs_change_node_prop($root, $path, $name, $value) {}
function svn_repos_fs_commit_txn($txn) {}
function svn_fs_begin_txn2($repos, $rev) {}
function svn_repos_fs($repos) {}
function svn_fs_node_prop($fsroot, $path, $propname) {}
function svn_update($path, $revno, $recurse) {}
function svn_repos_fs_begin_txn_for_commit($repos, $rev, $author, $log_msg) {}
function svn_log($repos_url, $start_revision, $end_revision, $limit, $flags) {}
function svn_fs_dir_entries($fsroot, $path) {}
function svn_fs_props_changed($root1, $path1, $root2, $path2) {}
function svn_fs_abort_txn($txn) {}
function svn_auth_get_parameter($key) {}
function svn_fs_node_created_rev($fsroot, $path) {}
function svn_import($path, $url, $nonrecursive) {}
function svn_client_version() {}
function svn_fs_revision_root($fs, $revnum) {}
function svn_checkout($repos, $targetpath, $revision, $flags) {}
function svn_diff($path1, $rev1, $path2, $rev2) {}
function svn_cleanup($workingdir) {}
function svn_fs_contents_changed($root1, $path1, $root2, $path2) {}
function svn_ls($repos_url, $revision_no, $recurse) {}
function svn_commit($log, $targets, $dontrecurse) {}
function svn_fs_make_dir($root, $path) {}
function svn_repos_hotcopy($repospath, $destpath, $cleanlogs) {}
function svn_auth_set_parameter($key, $value) {}
function stream_socket_recvfrom($socket, $length, $flags, $address) {}
function stream_filter_register($filtername, $classname) {}
function stream_get_transports() {}
function stream_set_blocking($stream, $mode) {}
function stream_context_create($options, $params) {}
function stream_set_write_buffer($stream, $buffer) {}
function stream_bucket_append($brigade, $bucket) {}
function stream_select($read, $write, $except, $tv_sec, $tv_usec) {}
function stream_encoding($stream, $encoding) {}
function stream_get_wrappers() {}
function stream_bucket_prepend($brigade, $bucket) {}
function stream_socket_accept($server_socket, $timeout, $peername) {}
function stream_wrapper_unregister($protocol) {}
function stream_wrapper_register($protocol, $classname) {}
function stream_filter_prepend($stream, $filtername, $read_write, $params) {}
function stream_context_get_default($options) {}
function stream_set_timeout($stream, $seconds, $microseconds) {}
function stream_socket_shutdown($stream, $how) {}
function stream_socket_client($remote_socket, $errno, $errstr, $timeout, $flags, $context) {}
function stream_socket_sendto($socket, $data, $flags, $address) {}
function stream_bucket_new($stream, $buffer) {}
function stream_filter_remove($stream_filter) {}
function stream_get_contents($handle, $maxlength, $offset) {}
function stream_socket_get_name($handle, $want_peer) {}
function stream_get_meta_data($stream) {}
function stream_wrapper_restore($protocol) {}
function stream_socket_enable_crypto($stream, $enable, $crypto_type, $session_stream) {}
function stream_get_line($handle, $length, $ending) {}
function stream_socket_server($local_socket, $errno, $errstr, $flags, $context) {}
function stream_context_set_option($stream_or_context, $wrapper, $option, $value) {}
function stream_notification_callback($notification_code, $severity, $message, $message_code, $bytes_transferred, $bytes_max) {}
function stream_copy_to_stream($source, $dest, $maxlength, $offset) {}
function stream_get_filters() {}
function stream_socket_pair($domain, $type, $protocol) {}
function stream_context_set_params($stream_or_context, $params) {}
function stream_context_get_options($stream_or_context) {}
function stream_resolve_include_path($filename, $context) {}
function stream_filter_append($stream, $filtername, $read_write, $params) {}
function stream_bucket_make_writeable($brigade) {}
function libxml_set_streams_context($streams_context) {}
function libxml_get_errors() {}
function libxml_clear_errors() {}
function libxml_get_last_error() {}
function libxml_use_internal_errors($use_errors) {}
function PDF_define_layer($pdfdoc, $name, $optlist) {}
function PDF_end_template($p) {}
function PDF_rotate($p, $phi) {}
function PDF_rect($p, $x, $y, $width, $height) {}
function PDF_fit_image($pdfdoc, $image, $x, $y, $optlist) {}
function PDF_setgray_stroke($p, $g) {}
function PDF_get_errmsg($pdfdoc) {}
function PDF_get_errnum($pdfdoc) {}
function PDF_load_image($pdfdoc, $imagetype, $filename, $optlist) {}
function PDF_setcolor($p, $fstype, $colorspace, $c1, $c2, $c3, $c4) {}
function PDF_setfont($pdfdoc, $font, $fontsize) {}
function PDF_get_minorversion() {}
function PDF_add_locallink($pdfdoc, $lowerleftx, $lowerlefty, $upperrightx, $upperrighty, $page, $dest) {}
function PDF_resume_page($pdfdoc, $optlist) {}
function PDF_findfont($p, $fontname, $encoding, $embed) {}
function PDF_set_value($p, $key, $value) {}
function PDF_pcos_get_string($p, $doc, $path) {}
function PDF_set_border_color($p, $red, $green, $blue) {}
function PDF_set_text_pos($p, $x, $y) {}
function PDF_lineto($p, $x, $y) {}
function PDF_attach_file($pdfdoc, $llx, $lly, $urx, $ury, $filename, $description, $author, $mimetype, $icon) {}
function PDF_pcos_get_stream($p, $doc, $optlist, $path) {}
function PDF_setdashpattern($pdfdoc, $optlist) {}
function PDF_get_majorversion() {}
function PDF_utf16_to_utf8($pdfdoc, $utf16string) {}
function PDF_add_launchlink($pdfdoc, $llx, $lly, $urx, $ury, $filename) {}
function PDF_stroke($p) {}
function PDF_add_note($pdfdoc, $llx, $lly, $urx, $ury, $contents, $title, $icon, $open) {}
function PDF_load_iccprofile($pdfdoc, $profilename, $optlist) {}
function PDF_create_fieldgroup($pdfdoc, $name, $optlist) {}
function PDF_moveto($p, $x, $y) {}
function PDF_create_action($pdfdoc, $type, $optlist) {}
function PDF_utf8_to_utf16($pdfdoc, $utf8string, $ordering) {}
function PDF_close($p) {}
function PDF_set_border_style($pdfdoc, $style, $width) {}
function PDF_fit_textflow($pdfdoc, $textflow, $llx, $lly, $urx, $ury, $optlist) {}
function PDF_open_pdi_page($p, $doc, $pagenumber, $optlist) {}
function PDF_create_pvf($pdfdoc, $filename, $data, $optlist) {}
function PDF_begin_template_ext($pdfdoc, $width, $height, $optlist) {}
function PDF_closepath_fill_stroke($p) {}
function PDF_setrgbcolor($p, $red, $green, $blue) {}
function PDF_end_document($pdfdoc, $optlist) {}
function PDF_close_pdi($p, $doc) {}
function PDF_end_item($pdfdoc, $id) {}
function PDF_create_field($pdfdoc, $llx, $lly, $urx, $ury, $name, $type, $optlist) {}
function PDF_arc($p, $x, $y, $r, $alpha, $beta) {}
function PDF_show_boxed($p, $text, $left, $top, $width, $height, $mode, $feature) {}
function PDF_get_pdi_value($p, $key, $doc, $page, $reserved) {}
function PDF_closepath($p) {}
function PDF_set_border_dash($pdfdoc, $black, $white) {}
function PDF_process_pdi($pdfdoc, $doc, $page, $optlist) {}
function PDF_makespotcolor($p, $spotname) {}
function PDF_open_memory_image($p, $image) {}
function PDF_add_nameddest($pdfdoc, $name, $optlist) {}
function PDF_set_info($p, $key, $value) {}
function PDF_open_pdi($pdfdoc, $filename, $optlist, $len) {}
function PDF_delete($pdfdoc) {}
function PDF_begin_item($pdfdoc, $tag, $optlist) {}
function PDF_fill($p) {}
function PDF_arcn($p, $x, $y, $r, $alpha, $beta) {}
function PDF_info_table($pdfdoc, $table, $keyword) {}
function PDF_delete_table($pdfdoc, $table, $optlist) {}
function PDF_setgray($p, $g) {}
function PDF_setflat($pdfdoc, $flatness) {}
function PDF_begin_font($pdfdoc, $filename, $a, $b, $c, $d, $e, $f, $optlist) {}
function PDF_end_page_ext($pdfdoc, $optlist) {}
function PDF_circle($pdfdoc, $x, $y, $r) {}
function PDF_add_pdflink($pdfdoc, $bottom_left_x, $bottom_left_y, $up_right_x, $up_right_y, $filename, $page, $dest) {}
function PDF_curveto($p, $x1, $y1, $x2, $y2, $x3, $y3) {}
function PDF_clip($p) {}
function PDF_restore($p) {}
function PDF_begin_document($pdfdoc, $filename, $optlist) {}
function PDF_fill_imageblock($pdfdoc, $page, $blockname, $image, $optlist) {}
function PDF_info_textflow($pdfdoc, $textflow, $keyword) {}
function PDF_create_annotation($pdfdoc, $llx, $lly, $urx, $ury, $type, $optlist) {}
function PDF_scale($p, $sx, $sy) {}
function PDF_utf32_to_utf16($pdfdoc, $utf32string, $ordering) {}
function PDF_begin_page_ext($pdfdoc, $width, $height, $optlist) {}
function PDF_initgraphics($p) {}
function PDF_get_value($p, $key, $modifier) {}
function PDF_fit_pdi_page($pdfdoc, $page, $x, $y, $optlist) {}
function PDF_setlinecap($p, $linecap) {}
function PDF_set_parameter($p, $key, $value) {}
function PDF_translate($p, $tx, $ty) {}
function PDF_create_gstate($pdfdoc, $optlist) {}
function PDF_pcos_get_number($p, $doc, $path) {}
function PDF_close_image($p, $image) {}
function PDF_shading_pattern($pdfdoc, $shading, $optlist) {}
function PDF_add_textflow($pdfdoc, $textflow, $text, $optlist) {}
function PDF_fit_textline($pdfdoc, $text, $x, $y, $optlist) {}
function PDF_setlinejoin($p, $value) {}
function PDF_setrgbcolor_stroke($p, $red, $green, $blue) {}
function PDF_create_textflow($pdfdoc, $text, $optlist) {}
function PDF_open_image($p, $imagetype, $source, $data, $length, $width, $height, $components, $bpc, $params) {}
function PDF_place_image($pdfdoc, $image, $x, $y, $scale) {}
function PDF_get_parameter($p, $key, $modifier) {}
function PDF_info_matchbox($pdfdoc, $boxname, $num, $keyword) {}
function PDF_setlinewidth($p, $width) {}
function PDF_info_textline($pdfdoc, $text, $keyword, $optlist) {}
function PDF_show($pdfdoc, $text) {}
function PDF_get_pdi_parameter($p, $key, $doc, $page, $reserved) {}
function PDF_endpath($p) {}
function PDF_shfill($pdfdoc, $shading) {}
function PDF_shading($pdfdoc, $shtype, $x0, $y0, $x1, $y1, $c1, $c2, $c3, $c4, $optlist) {}
function PDF_continue_text($p, $text) {}
function PDF_activate_item($pdfdoc, $id) {}
function PDF_end_glyph($pdfdoc) {}
function PDF_load_font($pdfdoc, $fontname, $encoding, $optlist) {}
function PDF_fill_pdfblock($pdfdoc, $page, $blockname, $contents, $optlist) {}
function PDF_close_pdi_page($p, $page) {}
function PDF_setmiterlimit($pdfdoc, $miter) {}
function PDF_add_thumbnail($pdfdoc, $image) {}
function PDF_delete_textflow($pdfdoc, $textflow) {}
function PDF_show_xy($p, $text, $x, $y) {}
function PDF_setgray_fill($p, $g) {}
function PDF_begin_template($pdfdoc, $width, $height) {}
function PDF_setrgbcolor_fill($p, $red, $green, $blue) {}
function PDF_delete_pvf($pdfdoc, $filename) {}
function PDF_add_table_cell($pdfdoc, $table, $column, $row, $text, $optlist) {}
function PDF_load_3ddata($pdfdoc, $filename, $optlist) {}
function PDF_suspend_page($pdfdoc, $optlist) {}
function PDF_begin_page($pdfdoc, $width, $height) {}
function PDF_set_gstate($pdfdoc, $gstate) {}
function PDF_encoding_set_char($pdfdoc, $encoding, $slot, $glyphname, $uv) {}
function PDF_open_ccitt($pdfdoc, $filename, $width, $height, $BitReverse, $k, $Blackls1) {}
function PDF_setdash($pdfdoc, $b, $w) {}
function PDF_closepath_stroke($p) {}
function PDF_create_bookmark($pdfdoc, $text, $optlist) {}
function PDF_get_apiname($pdfdoc) {}
function PDF_open_image_file($p, $imagetype, $filename, $stringparam, $intparam) {}
function PDF_stringwidth($p, $text, $font, $fontsize) {}
function PDF_end_pattern($p) {}
function PDF_setmatrix($p, $a, $b, $c, $d, $e, $f) {}
function PDF_skew($p, $alpha, $beta) {}
function PDF_create_3dview($pdfdoc, $username, $optlist) {}
function PDF_add_weblink($pdfdoc, $lowerleftx, $lowerlefty, $upperrightx, $upperrighty, $url) {}
function PDF_get_buffer($p) {}
function PDF_fill_stroke($p) {}
function PDF_set_layer_dependency($pdfdoc, $type, $optlist) {}
function PDF_save($p) {}
function PDF_begin_layer($pdfdoc, $layer) {}
function PDF_fill_textblock($pdfdoc, $page, $blockname, $text, $optlist) {}
function PDF_end_layer($pdfdoc) {}
function PDF_end_page($p) {}
function PDF_place_pdi_page($pdfdoc, $page, $x, $y, $sx, $sy) {}
function PDF_open_file($p, $filename) {}
function PDF_fit_table($pdfdoc, $table, $llx, $lly, $urx, $ury, $optlist) {}
function PDF_concat($p, $a, $b, $c, $d, $e, $f) {}
function PDF_begin_pattern($pdfdoc, $width, $height, $xstep, $ystep, $painttype) {}
function PDF_end_font($pdfdoc) {}
function PDF_begin_glyph($pdfdoc, $glyphname, $wx, $llx, $lly, $urx, $ury) {}
function PDF_new() {}
function ps_setlinejoin($psdoc, $type) {}
function ps_close_image($psdoc, $imageid) {}
function ps_set_parameter($psdoc, $name, $value) {}
function ps_setmiterlimit($psdoc, $value) {}
function ps_open_image($psdoc, $type, $source, $data, $lenght, $width, $height, $components, $bpc, $params) {}
function ps_closepath($psdoc) {}
function ps_moveto($psdoc, $x, $y) {}
function ps_save($psdoc) {}
function ps_place_image($psdoc, $imageid, $x, $y, $scale) {}
function ps_show($psdoc, $text) {}
function ps_end_pattern($psdoc) {}
function ps_rotate($psdoc, $rot) {}
function ps_delete($psdoc) {}
function ps_shfill($psdoc, $shadingid) {}
function ps_setlinewidth($psdoc, $width) {}
function ps_add_weblink($psdoc, $llx, $lly, $urx, $ury, $url) {}
function ps_show_xy2($psdoc, $text, $len, $xcoor, $ycoor) {}
function ps_scale($psdoc, $x, $y) {}
function ps_get_value($psdoc, $name, $modifier) {}
function ps_add_note($psdoc, $llx, $lly, $urx, $ury, $contents, $title, $icon, $open) {}
function ps_setlinecap($psdoc, $type) {}
function ps_get_buffer($psdoc) {}
function ps_begin_page($psdoc, $width, $height) {}
function ps_get_parameter($psdoc, $name, $modifier) {}
function ps_include_file($psdoc, $file) {}
function ps_restore($psdoc) {}
function ps_stroke($psdoc) {}
function ps_clip($psdoc) {}
function ps_set_text_pos($psdoc, $x, $y) {}
function ps_symbol_name($psdoc, $ord, $fontid) {}
function ps_shading($psdoc, $type, $x0, $y0, $x1, $y1, $c1, $c2, $c3, $c4, $optlist) {}
function ps_fill($psdoc) {}
function ps_setfont($psdoc, $fontid, $size) {}
function ps_show_xy($psdoc, $text, $x, $y) {}
function ps_begin_pattern($psdoc, $width, $height, $xstep, $ystep, $painttype) {}
function ps_setcolor($psdoc, $type, $colorspace, $c1, $c2, $c3, $c4) {}
function ps_closepath_stroke($psdoc) {}
function ps_symbol_width($psdoc, $ord, $fontid, $size) {}
function ps_makespotcolor($psdoc, $name, $reserved) {}
function ps_symbol($psdoc, $ord) {}
function ps_add_launchlink($psdoc, $llx, $lly, $urx, $ury, $filename) {}
function ps_stringwidth($psdoc, $text, $fontid, $size) {}
function ps_setpolydash($psdoc, $arr) {}
function ps_set_border_dash($psdoc, $black, $white) {}
function ps_string_geometry($psdoc, $text, $fontid, $size) {}
function ps_shading_pattern($psdoc, $shadingid, $optlist) {}
function ps_lineto($psdoc, $x, $y) {}
function ps_translate($psdoc, $x, $y) {}
function ps_new() {}
function ps_findfont($psdoc, $fontname, $encoding, $embed) {}
function ps_setdash($psdoc, $on, $off) {}
function ps_set_border_style($psdoc, $style, $width) {}
function ps_set_info($p, $key, $val) {}
function ps_set_value($psdoc, $name, $value) {}
function ps_setgray($psdoc, $gray) {}
function ps_setoverprintmode($psdoc, $mode) {}
function ps_arc($psdoc, $x, $y, $radius, $alpha, $beta) {}
function ps_add_locallink($psdoc, $llx, $lly, $urx, $ury, $page, $dest) {}
function ps_rect($psdoc, $x, $y, $width, $height) {}
function ps_end_template($psdoc) {}
function ps_arcn($psdoc, $x, $y, $radius, $alpha, $beta) {}
function ps_show_boxed($psdoc, $text, $left, $bottom, $width, $height, $hmode, $feature) {}
function ps_begin_template($psdoc, $width, $height) {}
function ps_circle($psdoc, $x, $y, $radius) {}
function ps_close($psdoc) {}
function ps_show2($psdoc, $text, $len) {}
function ps_set_border_color($psdoc, $red, $green, $blue) {}
function ps_add_pdflink($psdoc, $llx, $lly, $urx, $ury, $filename, $page, $dest) {}
function ps_open_file($psdoc, $filename) {}
function ps_setflat($psdoc, $value) {}
function ps_continue_text($psdoc, $text) {}
function ps_end_page($psdoc) {}
function ps_open_image_file($psdoc, $type, $filename, $stringparam, $intparam) {}
function ps_hyphenate($psdoc, $text) {}
function ps_open_memory_image($psdoc, $gd) {}
function ps_fill_stroke($psdoc) {}
function ps_add_bookmark($psdoc, $text, $parent, $open) {}
function ps_curveto($psdoc, $x1, $y1, $x2, $y2, $x3, $y3) {}
function dba_sync($handle) {}
function dba_insert($key, $value, $handle) {}
function dba_list() {}
function dba_exists($key, $handle) {}
function dba_fetch($key, $handle) {}
function dba_handlers($full_info) {}
function dba_firstkey($handle) {}
function dba_delete($key, $handle) {}
function dba_key_split($key) {}
function dba_open($path, $mode, $handler) {}
function dba_close($handle) {}
function dba_replace($key, $value, $handle) {}
function dba_popen($path, $mode, $handler) {}
function dba_optimize($handle) {}
function dba_nextkey($handle) {}
function gethostbynamel($hostname) {}
function getprotobyname($name) {}
function pfsockopen($hostname, $port, $errno, $errstr, $timeout) {}
function gethostbyname($hostname) {}
function dns_get_record($hostname, $type) {}
function openlog($ident, $option, $facility) {}
function gethostbyaddr($ip_address) {}
function getmxrr($hostname, $mxhosts, $weight) {}
function getprotobynumber($number) {}
function inet_ntop($in_addr) {}
function ip2long($ip_address) {}
function headers_sent($file, $line) {}
function setcookie($name, $value, $expire, $path, $domain, $secure, $httponly) {}
function long2ip($proper_address) {}
function syslog($priority, $message) {}
function define_syslog_variables() {}
function checkdnsrr($host, $type) {}
function header($string, $replace, $http_response_code) {}
function getservbyname($service, $protocol) {}
function setrawcookie($name, $value, $expire, $path, $domain, $secure, $httponly) {}
function inet_pton($address) {}
function headers_list() {}
function getservbyport($port, $protocol) {}
function closelog() {}
function fsockopen($hostname, $port, $errno, $errstr, $timeout) {}
function sqlite_has_prev($result) {}
function sqlite_error_string($error_code) {}
function sqlite_prev($result) {}
function sqlite_current($result, $result_type, $decode_binary) {}
function sqlite_rewind($result) {}
function sqlite_changes($dbhandle) {}
function sqlite_has_more($result) {}
function sqlite_escape_string($item) {}
function sqlite_create_function($dbhandle, $function_name, $callback, $num_args) {}
function sqlite_fetch_array($result, $result_type, $decode_binary) {}
function sqlite_valid($result) {}
function sqlite_fetch_all($result, $result_type, $decode_binary) {}
function sqlite_close($dbhandle) {}
function sqlite_popen($filename, $mode, $error_message) {}
function sqlite_fetch_single($result, $decode_binary) {}
function sqlite_unbuffered_query($dbhandle, $query, $result_type, $error_msg) {}
function sqlite_query($dbhandle, $query, $result_type, $error_msg) {}
function sqlite_num_rows($result) {}
function sqlite_column($result, $index_or_name, $decode_binary) {}
function sqlite_libencoding() {}
function sqlite_fetch_object($result, $class_name, $ctor_params, $decode_binary) {}
function sqlite_array_query($dbhandle, $query, $result_type, $decode_binary) {}
function sqlite_exec($dbhandle, $query, $error_msg) {}
function sqlite_factory($filename, $mode, $error_message) {}
function sqlite_busy_timeout($dbhandle, $milliseconds) {}
function sqlite_next($result) {}
function sqlite_udf_encode_binary($data) {}
function sqlite_fetch_column_types($table_name, $dbhandle, $result_type) {}
function sqlite_single_query($db, $query, $first_row_only, $decode_binary) {}
function sqlite_create_aggregate($dbhandle, $function_name, $step_func, $finalize_func, $num_args) {}
function sqlite_udf_decode_binary($data) {}
function sqlite_seek($result, $rownum) {}
function sqlite_last_error($dbhandle) {}
function sqlite_num_fields($result) {}
function sqlite_key($result) {}
function sqlite_libversion() {}
function sqlite_open($filename, $mode, $error_message) {}
function sqlite_field_name($result, $field_index) {}
function sqlite_last_insert_rowid($dbhandle) {}
function domxml_open_file($filename, $mode, $error) {}
function domxml_open_mem($str, $mode, $error) {}
function domxml_xslt_stylesheet_doc($xsl_doc) {}
function domxml_new_doc($version) {}
function xpath_new_context($dom_document) {}
function xpath_eval($xpath_context, $xpath_expression, $contextnode) {}
function xpath_register_ns($xpath_context, $prefix, $uri) {}
function xptr_new_context() {}
function domxml_xslt_stylesheet($xsl_buf) {}
function domxml_xmltree($str) {}
function domxml_xslt_stylesheet_file($xsl_file) {}
function xptr_eval($xpath_context, $eval_str, $contextnode) {}
function xpath_eval_expression($xpath_context, $expression, $contextnode) {}
function domxml_version() {}
function domxml_xslt_version() {}
function xpath_register_ns_auto($xpath_context, $context_node) {}
function bzerror($bz) {}
function bzclose($bz) {}
function bzerrno($bz) {}
function bzerrstr($bz) {}
function bzread($bz, $length) {}
function bzcompress($source, $blocksize, $workfactor) {}
function bzwrite($bz, $data, $length) {}
function bzdecompress($source, $small) {}
function bzopen($filename, $mode) {}
function bzflush($bz) {}
function xmlrpc_server_add_introspection_data($server, $desc) {}
function xmlrpc_server_destroy($server) {}
function xmlrpc_server_register_method($server, $method_name, $function) {}
function xmlrpc_parse_method_descriptions($xml) {}
function xmlrpc_get_type($value) {}
function xmlrpc_decode_request($xml, $method, $encoding) {}
function xmlrpc_server_create() {}
function xmlrpc_encode_request($method, $params, $output_options) {}
function xmlrpc_is_fault($arg) {}
function xmlrpc_encode($value) {}
function xmlrpc_decode($xml, $encoding) {}
function xmlrpc_server_register_introspection_callback($server, $function) {}
function xmlrpc_set_type($value, $type) {}
function xmlrpc_server_call_method($server, $xml, $user_data, $output_options) {}
function ssh2_sftp_rename($sftp, $from, $to) {}
function ssh2_auth_none($session, $username) {}
function ssh2_fetch_stream($channel, $streamid) {}
function ssh2_connect($host, $port, $methods, $callbacks) {}
function ssh2_auth_password($session, $username, $password) {}
function ssh2_sftp_stat($sftp, $path) {}
function ssh2_publickey_init($session) {}
function ssh2_publickey_add($pkey, $algoname, $blob, $overwrite, $attributes) {}
function ssh2_fingerprint($session, $flags) {}
function ssh2_scp_recv($session, $remote_file, $local_file) {}
function ssh2_sftp_symlink($sftp, $target, $link) {}
function ssh2_auth_hostbased_file($session, $username, $hostname, $pubkeyfile, $privkeyfile, $passphrase, $local_username) {}
function ssh2_methods_negotiated($session) {}
function ssh2_sftp_mkdir($sftp, $dirname, $mode, $recursive) {}
function ssh2_sftp_unlink($sftp, $filename) {}
function ssh2_sftp_readlink($sftp, $link) {}
function ssh2_sftp_lstat($sftp, $path) {}
function ssh2_sftp($session) {}
function ssh2_scp_send($session, $local_file, $remote_file, $create_mode) {}
function ssh2_tunnel($session, $host, $port) {}
function ssh2_publickey_remove($pkey, $algoname, $blob) {}
function ssh2_sftp_rmdir($sftp, $dirname) {}
function ssh2_shell($session, $term_type, $env, $width, $height, $width_height_type) {}
function ssh2_sftp_realpath($sftp, $filename) {}
function ssh2_publickey_list($pkey) {}
function ssh2_exec($session, $command, $pty, $env, $width, $height, $width_height_type) {}
function ssh2_auth_pubkey_file($session, $username, $pubkeyfile, $privkeyfile, $passphrase) {}
function fam_open($appname) {}
function fam_cancel_monitor($fam, $fam_monitor) {}
function fam_suspend_monitor($fam, $fam_monitor) {}
function fam_pending($fam) {}
function fam_resume_monitor($fam, $fam_monitor) {}
function fam_close($fam) {}
function fam_monitor_file($fam, $filename) {}
function fam_monitor_collection($fam, $dirname, $depth, $mask) {}
function fam_next_event($fam) {}
function fam_monitor_directory($fam, $dirname) {}
function ibase_server_info($service_handle, $action) {}
function ibase_commit_ret($link_or_trans_identifier) {}
function ibase_modify_user($service_handle, $user_name, $password, $first_name, $middle_name, $last_name) {}
function ibase_commit($link_or_trans_identifier) {}
function ibase_free_result($result_identifier) {}
function ibase_fetch_object($result_id, $fetch_flag) {}
function ibase_query($link_identifier, $query, $bind_args) {}
function ibase_blob_cancel($blob_handle) {}
function ibase_connect($database, $username, $password, $charset, $buffers, $dialect, $role, $sync) {}
function ibase_set_event_handler($event_handler, $event_name1, $event_name2) {}
function ibase_param_info($query, $param_number) {}
function ibase_close($connection_id) {}
function ibase_prepare($query) {}
function ibase_db_info($service_handle, $db, $action, $argument) {}
function ibase_fetch_row($result_identifier, $fetch_flag) {}
function ibase_timefmt($format, $columntype) {}
function ibase_maintain_db($service_handle, $db, $action, $argument) {}
function ibase_gen_id($generator, $increment, $link_identifier) {}
function ibase_affected_rows($link_identifier) {}
function ibase_num_params($query) {}
function ibase_num_fields($result_id) {}
function ibase_service_detach($service_handle) {}
function ibase_drop_db($connection) {}
function ibase_restore($service_handle, $source_file, $dest_db, $options, $verbose) {}
function ibase_errmsg() {}
function ibase_add_user($service_handle, $user_name, $password, $first_name, $middle_name, $last_name) {}
function ibase_trans($trans_args, $link_identifier) {}
function ibase_blob_info($link_identifier, $blob_id) {}
function ibase_free_query($query) {}
function ibase_blob_import($link_identifier, $file_handle) {}
function ibase_blob_add($blob_handle, $data) {}
function ibase_blob_create($link_identifier) {}
function ibase_name_result($result, $name) {}
function ibase_errcode() {}
function ibase_rollback_ret($link_or_trans_identifier) {}
function ibase_free_event_handler($event) {}
function ibase_delete_user($service_handle, $user_name) {}
function ibase_blob_get($blob_handle, $len) {}
function ibase_service_attach($host, $dba_username, $dba_password) {}
function ibase_blob_open($link_identifier, $blob_id) {}
function ibase_pconnect($database, $username, $password, $charset, $buffers, $dialect, $role, $sync) {}
function ibase_fetch_assoc($result, $fetch_flag) {}
function ibase_field_info($result, $field_number) {}
function ibase_execute($query, $bind_arg) {}
function ibase_backup($service_handle, $source_db, $dest_file, $options, $verbose) {}
function ibase_blob_echo($link_identifier, $blob_id) {}
function ibase_wait_event($event_name1, $event_name2) {}
function ibase_blob_close($blob_handle) {}
function ibase_rollback($link_or_trans_identifier) {}
function iconv_mime_decode_headers($encoded_headers, $mode, $charset) {}
function iconv_substr($str, $offset) {}
function iconv_strlen($str, $charset) {}
function iconv($in_charset, $out_charset, $str) {}
function iconv_mime_decode($encoded_header, $mode, $charset) {}
function iconv_strrpos($haystack, $needle, $charset) {}
function iconv_set_encoding($type, $charset) {}
function iconv_strpos($haystack, $needle, $offset, $charset) {}
function ob_iconv_handler($contents, $status) {}
function iconv_mime_encode($field_name, $field_value, $preferences) {}
function iconv_get_encoding($type) {}
function exif_read_data($filename, $sections, $arrays, $thumbnail) {}
function exif_thumbnail($filename, $width, $height, $imagetype) {}
function exif_imagetype($filename) {}
function exif_tagname($index) {}
function win32_start_service_ctrl_dispatcher($name) {}
function win32_delete_service($servicename, $machine) {}
function win32_set_service_status($status) {}
function win32_create_service($details, $machine) {}
function win32_stop_service($servicename, $machine) {}
function win32_get_last_control_message() {}
function win32_start_service($servicename, $machine) {}
function win32_query_service_status($servicename, $machine) {}
function dbplus_undo($relation) {}
function dbplus_rsecindex($relation, $domlist, $type) {}
function dbplus_xlockrel($relation) {}
function dbplus_chdir($newdir) {}
function dbplus_freelock($relation, $tuple) {}
function dbplus_tremove($relation, $tuple, $current) {}
function dbplus_restorepos($relation, $tuple) {}
function dbplus_next($relation, $tuple) {}
function dbplus_setindexbynumber($relation, $idx_number) {}
function dbplus_xunlockrel($relation) {}
function dbplus_undoprepare($relation) {}
function dbplus_unlockrel($relation) {}
function dbplus_resolve($relation_name) {}
function dbplus_setindex($relation, $idx_name) {}
function dbplus_rcreate($name, $domlist, $overwrite) {}
function dbplus_close($relation) {}
function dbplus_errno() {}
function dbplus_ropen($name) {}
function dbplus_rchperm($relation, $mask, $user, $group) {}
function dbplus_lockrel($relation) {}
function dbplus_errcode($errno) {}
function dbplus_rquery($query, $dbpath) {}
function dbplus_first($relation, $tuple) {}
function dbplus_savepos($relation) {}
function dbplus_freealllocks() {}
function dbplus_rzap($relation) {}
function dbplus_flush($relation) {}
function dbplus_find($relation, $constraints, $tuple) {}
function dbplus_tcl($sid, $script) {}
function dbplus_getunique($relation, $uniqueid) {}
function dbplus_getlock($relation, $tuple) {}
function dbplus_rcrtexact($name, $relation, $overwrite) {}
function dbplus_freerlocks($relation) {}
function dbplus_aql($query, $server, $dbpath) {}
function dbplus_prev($relation, $tuple) {}
function dbplus_add($relation, $tuple) {}
function dbplus_info($relation, $key, $result) {}
function dbplus_open($name) {}
function dbplus_sql($query, $server, $dbpath) {}
function dbplus_rrename($relation, $name) {}
function dbplus_unselect($relation) {}
function dbplus_last($relation, $tuple) {}
function dbplus_rkeys($relation, $domlist) {}
function dbplus_runlink($relation) {}
function dbplus_update($relation, $old, $new) {}
function dbplus_rcrtlike($name, $relation, $overwrite) {}
function dbplus_curr($relation, $tuple) {}
function bcmul($left_operand, $right_operand, $scale) {}
function bccomp($left_operand, $right_operand, $scale) {}
function bcsub($left_operand, $right_operand, $scale) {}
function bcmod($left_operand, $modulus) {}
function bcpowmod($left_operand, $right_operand, $modulus, $scale) {}
function bcdiv($left_operand, $right_operand, $scale) {}
function bcscale($scale) {}
function bcpow($left_operand, $right_operand, $scale) {}
function bcsqrt($operand, $scale) {}
function bcadd($left_operand, $right_operand, $scale) {}
function simplexml_load_file($filename, $class_name, $options, $ns, $is_prefix) {}
function simplexml_import_dom($node, $class_name) {}
function simplexml_load_string($data, $class_name, $options, $ns, $is_prefix) {}
function mime_content_type($filename) {}
function json_encode($value) {}
function json_decode($json, $assoc) {}
function base64_encode($data) {}
function urlencode($str) {}
function rawurldecode($str) {}
function parse_url($url, $component) {}
function rawurlencode($str) {}
function base64_decode($data, $strict) {}
function http_build_query($formdata, $numeric_prefix, $arg_separator) {}
function get_meta_tags($filename, $use_include_path) {}
function get_headers($url, $format) {}
function urldecode($str) {}
function msql_close($link_identifier) {}
function msql_result($result, $row, $field) {}
function msql_free_result($result) {}
function msql_field_len($result, $field_offset) {}
function msql_data_seek($result, $row_number) {}
function msql_field_flags($result, $field_offset) {}
function msql_field_seek($result, $field_offset) {}
function msql_error() {}
function msql_list_tables($database, $link_identifier) {}
function msql_num_rows($query_identifier) {}
function msql_list_fields($database, $tablename, $link_identifier) {}
function msql_field_table($result, $field_offset) {}
function msql_list_dbs($link_identifier) {}
function msql_field_name($result, $field_offset) {}
function msql_fetch_row($result) {}
function msql_fetch_array($result, $result_type) {}
function msql_affected_rows($result) {}
function msql_query($query, $link_identifier) {}
function msql_drop_db($database_name, $link_identifier) {}
function msql_field_type($result, $field_offset) {}
function msql_create_db($database_name, $link_identifier) {}
function msql_db_query($database, $query, $link_identifier) {}
function msql_fetch_object($result) {}
function msql_select_db($database_name, $link_identifier) {}
function msql_pconnect($hostname) {}
function msql_num_fields($result) {}
function msql_connect($hostname) {}
function msql_fetch_field($result, $field_offset) {}
function classkit_method_redefine($classname, $methodname, $args, $code, $flags) {}
function classkit_method_remove($classname, $methodname) {}
function classkit_method_add($classname, $methodname, $args, $code, $flags) {}
function classkit_method_copy($dClass, $dMethod, $sClass, $sMethod) {}
function classkit_method_rename($classname, $methodname, $newname) {}
function classkit_import($filename) {}
function hexdec($hex_string) {}
function max($values) {}
function exp($arg) {}
function decoct($number) {}
function fmod($x, $y) {}
function asinh($arg) {}
function sqrt($arg) {}
function mt_srand($seed) {}
function acos($arg) {}
function log($arg, $base) {}
function base_convert($number, $frombase, $tobase) {}
function mt_rand() {}
function rand() {}
function lcg_value() {}
function octdec($octal_string) {}
function pow($base, $exp) {}
function atan2($y, $x) {}
function is_nan($val) {}
function log1p($number) {}
function acosh($arg) {}
function round($val, $precision) {}
function log10($arg) {}
function pi() {}
function asin($arg) {}
function atanh($arg) {}
function floor($value) {}
function cosh($arg) {}
function decbin($number) {}
function getrandmax() {}
function bindec($binary_string) {}
function is_infinite($val) {}
function rad2deg($number) {}
function hypot($x, $y) {}
function mt_getrandmax() {}
function is_finite($val) {}
function cos($arg) {}
function atan($arg) {}
function tan($arg) {}
function dechex($number) {}
function sinh($arg) {}
function abs($number) {}
function sin($arg) {}
function min($values) {}
function tanh($arg) {}
function srand($seed) {}
function deg2rad($number) {}
function expm1($arg) {}
function ceil($value) {}
function ldap_mod_del($link_identifier, $dn, $entry) {}
function ldap_dn2ufn($dn) {}
function ldap_compare($link_identifier, $dn, $attribute, $value) {}
function ldap_read($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_count_entries($link_identifier, $result_identifier) {}
function ldap_explode_dn($dn, $with_attrib) {}
function ldap_add($link_identifier, $dn, $entry) {}
function ldap_search($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_list($link_identifier, $base_dn, $filter, $attributes, $attrsonly, $sizelimit, $timelimit, $deref) {}
function ldap_sasl_bind($link, $binddn, $password, $sasl_mech, $sasl_realm, $sasl_authz_id, $props) {}
function ldap_next_reference($link, $entry) {}
function ldap_parse_result($link, $result, $errcode, $matcheddn, $errmsg, $referrals) {}
function ldap_parse_reference($link, $entry, $referrals) {}
function ldap_err2str($errno) {}
function ldap_t61_to_8859($value) {}
function ldap_next_entry($link_identifier, $result_entry_identifier) {}
function ldap_delete($link_identifier, $dn) {}
function ldap_sort($link, $result, $sortfilter) {}
function ldap_connect($hostname, $port) {}
function ldap_get_attributes($link_identifier, $result_entry_identifier) {}
function ldap_set_rebind_proc($link, $callback) {}
function ldap_first_attribute($link_identifier, $result_entry_identifier) {}
function ldap_free_result($result_identifier) {}
function ldap_get_dn($link_identifier, $result_entry_identifier) {}
function ldap_get_values_len($link_identifier, $result_entry_identifier, $attribute) {}
function ldap_rename($link_identifier, $dn, $newrdn, $newparent, $deleteoldrdn) {}
function ldap_start_tls($link) {}
function ldap_set_option($link_identifier, $option, $newval) {}
function ldap_next_attribute($link_identifier, $result_entry_identifier) {}
function ldap_get_entries($link_identifier, $result_identifier) {}
function ldap_8859_to_t61($value) {}
function ldap_mod_replace($link_identifier, $dn, $entry) {}
function ldap_mod_add($link_identifier, $dn, $entry) {}
function ldap_error($link_identifier) {}
function ldap_errno($link_identifier) {}
function ldap_get_values($link_identifier, $result_entry_identifier, $attribute) {}
function ldap_get_option($link_identifier, $option, $retval) {}
function ldap_first_entry($link_identifier, $result_identifier) {}
function ldap_bind($link_identifier, $bind_rdn, $bind_password) {}
function ldap_modify($link_identifier, $dn, $entry) {}
function ldap_first_reference($link, $result) {}
function ldap_unbind($link_identifier) {}
function notes_version($database_name) {}
function notes_body($server, $mailbox, $msg_number) {}
function notes_drop_db($database_name) {}
function notes_search($database_name, $keywords) {}
function notes_create_db($database_name) {}
function notes_mark_read($database_name, $user_name, $note_id) {}
function notes_header_info($server, $mailbox, $msg_number) {}
function notes_find_note($database_name, $name, $type) {}
function notes_create_note($database_name, $form_name) {}
function notes_mark_unread($database_name, $user_name, $note_id) {}
function notes_copy_db($from_database_name, $to_database_name) {}
function notes_list_msgs($db) {}
function notes_nav_create($database_name, $name) {}
function notes_unread($database_name, $user_name) {}
function expect_popen($command) {}
function expect_expectl($expect, $cases, $match) {}
function nsapi_request_headers() {}
function nsapi_response_headers() {}
function nsapi_virtual($uri) {}
function mssql_bind($stmt, $param_name, $var, $type, $is_output, $is_null, $maxlen) {}
function mssql_min_error_severity($severity) {}
function mssql_get_last_message() {}
function mssql_field_seek($result, $field_offset) {}
function mssql_num_fields($result) {}
function mssql_num_rows($result) {}
function mssql_field_type($result, $offset) {}
function mssql_pconnect($servername, $username, $password, $new_link) {}
function mssql_execute($stmt, $skip_results) {}
function mssql_fetch_assoc($result_id) {}
function mssql_close($link_identifier) {}
function mssql_next_result($result_id) {}
function mssql_rows_affected($link_identifier) {}
function mssql_free_statement($stmt) {}
function mssql_fetch_batch($result) {}
function mssql_data_seek($result_identifier, $row_number) {}
function mssql_select_db($database_name, $link_identifier) {}
function mssql_init($sp_name, $link_identifier) {}
function mssql_fetch_field($result, $field_offset) {}
function mssql_result($result, $row, $field) {}
function mssql_free_result($result) {}
function mssql_min_message_severity($severity) {}
function mssql_fetch_array($result, $result_type) {}
function mssql_guid_string($binary, $short_format) {}
function mssql_connect($servername, $username, $password, $new_link) {}
function mssql_query($query, $link_identifier, $batch_size) {}
function mssql_fetch_object($result) {}
function mssql_fetch_row($result) {}
function mssql_field_length($result, $offset) {}
function mssql_field_name($result, $offset) {}
function wddx_add_vars($packet_id, $var_name) {}
function wddx_serialize_vars($var_name) {}
function wddx_serialize_value($var, $comment) {}
function wddx_unserialize($packet) {}
function wddx_packet_start($comment) {}
function wddx_packet_end($packet_id) {}
function runkit_constant_add($constname, $value) {}
function runkit_function_copy($funcname, $targetname) {}
function runkit_function_remove($funcname) {}
function runkit_class_emancipate($classname) {}
function runkit_method_redefine($classname, $methodname, $args, $code, $flags) {}
function runkit_lint_file($filename) {}
function runkit_method_rename($classname, $methodname, $newname) {}
function runkit_method_remove($classname, $methodname) {}
function runkit_import($filename, $flags) {}
function runkit_method_add($classname, $methodname, $args, $code, $flags) {}
function runkit_sandbox_output_handler($sandbox, $callback) {}
function runkit_constant_redefine($constname, $newvalue) {}
function runkit_lint($code) {}
function runkit_method_copy($dClass, $dMethod, $sClass, $sMethod) {}
function runkit_return_value_used() {}
function runkit_class_adopt($classname, $parentname) {}
function runkit_constant_remove($constname) {}
function runkit_function_rename($funcname, $newname) {}
function runkit_function_add($funcname, $arglist, $code) {}
function runkit_function_redefine($funcname, $arglist, $code) {}
function runkit_superglobals() {}
function dbx_connect($module, $host, $database, $username, $password, $persistent) {}
function dbx_error($link_identifier) {}
function dbx_close($link_identifier) {}
function dbx_compare($row_a, $row_b, $column_key, $flags) {}
function dbx_escape_string($link_identifier, $text) {}
function dbx_sort($result, $user_compare_function) {}
function dbx_fetch_row($result_identifier) {}
function dbx_query($link_identifier, $sql_statement, $flags) {}
function kadm5_chpass_principal($handle, $principal, $password) {}
function kadm5_get_policies($handle) {}
function kadm5_delete_principal($handle, $principal) {}
function kadm5_destroy($handle) {}
function kadm5_modify_principal($handle, $principal, $options) {}
function kadm5_flush($handle) {}
function kadm5_create_principal($handle, $principal, $password, $options) {}
function kadm5_get_principals($handle) {}
function kadm5_init_with_password($admin_server, $realm, $principal, $password) {}
function kadm5_get_principal($handle, $principal) {}
function apd_get_active_symbols() {}
function apd_callstack() {}
function apd_clunk($warning, $delimiter) {}
function apd_dump_persistent_resources() {}
function apd_set_session_trace($debug_level, $dump_directory) {}
function override_function($function_name, $function_args, $function_code) {}
function apd_dump_regular_resources() {}
function apd_croak($warning, $delimiter) {}
function apd_breakpoint($debug_level) {}
function apd_set_pprof_trace($dump_directory, $fragment) {}
function apd_echo($output) {}
function rename_function($original_name, $new_name) {}
function apd_set_socket_session_trace($tcp_server, $socket_type, $port, $debug_level) {}
function apd_set_session($debug_level) {}
function apd_continue($debug_level) {}
function apd_dump_function_table() {}
function restore_error_handler() {}
function set_exception_handler($exception_handler) {}
function set_error_handler($error_handler, $error_types) {}
function trigger_error($error_msg, $error_type) {}
function restore_exception_handler() {}
function error_get_last() {}
function error_log($message, $message_type, $destination, $extra_headers) {}
function debug_backtrace($provide_object) {}
function debug_print_backtrace() {}
function error_reporting($level) {}
function yaz_connect($zurl, $options) {}
function yaz_element($id, $elementset) {}
function yaz_scan($id, $type, $startterm, $flags) {}
function yaz_itemorder($id, $args) {}
function yaz_es_result($id) {}
function yaz_hits($id, $searchresult) {}
function yaz_set_option($id, $name, $value) {}
function yaz_errno($id) {}
function yaz_schema($id, $schema) {}
function yaz_addinfo($id) {}
function yaz_es($id, $type, $args) {}
function yaz_wait($options) {}
function yaz_close($id) {}
function yaz_scan_result($id, $result) {}
function yaz_ccl_conf($id, $config) {}
function yaz_record($id, $pos, $type) {}
function yaz_sort($id, $criteria) {}
function yaz_ccl_parse($id, $query, $result) {}
function yaz_search($id, $type, $query) {}
function yaz_present($id) {}
function yaz_get_option($id, $name) {}
function yaz_database($id, $databases) {}
function yaz_range($id, $start, $number) {}
function yaz_syntax($id, $syntax) {}
function yaz_error($id) {}
function jdtofrench($juliandaycount) {}
function cal_to_jd($calendar, $month, $day, $year) {}
function frenchtojd($month, $day, $year) {}
function unixtojd($timestamp) {}
function jdtojulian($julianday) {}
function easter_date($year) {}
function jdtounix($jday) {}
function cal_from_jd($jd, $calendar) {}
function gregoriantojd($month, $day, $year) {}
function jdmonthname($julianday, $mode) {}
function cal_info($calendar) {}
function cal_days_in_month($calendar, $month, $year) {}
function jdtogregorian($julianday) {}
function jddayofweek($julianday, $mode) {}
function jdtojewish($juliandaycount, $hebrew, $fl) {}
function juliantojd($month, $day, $year) {}
function jewishtojd($month, $day, $year) {}
function easter_days($year, $method) {}
function mhash_keygen_s2k($hash, $password, $salt, $bytes) {}
function mhash_get_hash_name($hash) {}
function mhash_get_block_size($hash) {}
function mhash_count() {}
function mhash($hash, $data, $key) {}
function strcoll($str1, $str2) {}
function vfprintf($handle, $format, $args) {}
function hebrevc($hebrew_text, $max_chars_per_line) {}
function chr($ascii) {}
function str_ireplace($search, $replace, $subject, $count) {}
function substr($string, $start, $length) {}
function substr_replace($string, $replacement, $start, $length) {}
function similar_text($first, $second, $percent) {}
function strip_tags($str, $allowable_tags) {}
function stripos($haystack, $needle, $offset) {}
function explode($delimiter, $string, $limit) {}
function quoted_printable_decode($str) {}
function strstr($haystack, $needle, $before_needle) {}
function sprintf($format, $args) {}
function implode($glue, $pieces) {}
function strrpos($haystack, $needle, $offset) {}
function lcfirst($str) {}
function md5($str, $raw_output) {}
function strpbrk($haystack, $char_list) {}
function get_html_translation_table($table, $quote_style) {}
function strtolower($str) {}
function str_rot13($str) {}
function addcslashes($str, $charlist) {}
function rtrim($str, $charlist) {}
function htmlspecialchars($string, $quote_style, $charset, $double_encode) {}
function crypt($str, $salt) {}
function quotemeta($str) {}
function ucwords($str) {}
function stripcslashes($str) {}
function crc32($str) {}
function stristr($haystack, $needle, $before_needle) {}
function strcasecmp($str1, $str2) {}
function addslashes($str) {}
function localeconv() {}
function substr_count($haystack, $needle, $offset, $length) {}
function bin2hex($str) {}
function setlocale($category, $locale) {}
function sha1($str, $raw_output) {}
function convert_uuencode($data) {}
function number_format($number, $decimals) {}
function strpos($haystack, $needle, $offset) {}
function stripslashes($str) {}
function html_entity_decode($string, $quote_style, $charset) {}
function str_pad($input, $pad_length, $pad_string, $pad_type) {}
function strtok($str, $token) {}
function ltrim($str, $charlist) {}
function strnatcmp($str1, $str2) {}
function strrchr($haystack, $needle) {}
function str_split($string, $split_length) {}
function strrev($string) {}
function count_chars($string, $mode) {}
function vprintf($format, $args) {}
function parse_str($str, $arr) {}
function wordwrap($str, $width, $break, $cut) {}
function money_format($format, $number) {}
function strnatcasecmp($str1, $str2) {}
function md5_file($filename, $raw_output) {}
function strspn($str1, $str2, $start, $length) {}
function hebrev($hebrew_text, $max_chars_per_line) {}
function strcspn($str1, $str2, $start, $length) {}
function htmlspecialchars_decode($string, $quote_style) {}
function sscanf($str, $format) {}
function str_shuffle($str) {}
function chunk_split($body, $chunklen, $end) {}
function sha1_file($filename, $raw_output) {}
function strlen($string) {}
function strtr($str, $from, $to) {}
function substr_compare($main_str, $str, $offset, $length, $case_insensitivity) {}
function printf($format, $args) {}
function strncasecmp($str1, $str2, $len) {}
function fprintf($handle, $format, $args) {}
function htmlentities($string, $quote_style, $charset, $double_encode) {}
function ucfirst($str) {}
function soundex($str) {}
function nl2br($string) {}
function strtoupper($string) {}
function strncmp($str1, $str2, $len) {}
function str_getcsv($input, $delimiter, $enclosure, $escape) {}
function levenshtein($str1, $str2) {}
function nl_langinfo($item) {}
function convert_cyr_string($str, $from, $to) {}
function strripos($haystack, $needle, $offset) {}
function str_replace($search, $replace, $subject, $count) {}
function trim($str, $charlist) {}
function ord($string) {}
function metaphone($str, $phones) {}
function str_repeat($input, $multiplier) {}
function vsprintf($format, $args) {}
function strcmp($str1, $str2) {}
function convert_uudecode($data) {}
function str_word_count($string, $format, $charlist) {}
function dbase_add_record($dbase_identifier, $record) {}
function dbase_pack($dbase_identifier) {}
function dbase_replace_record($dbase_identifier, $record, $record_number) {}
function dbase_create($filename, $fields) {}
function dbase_close($dbase_identifier) {}
function dbase_delete_record($dbase_identifier, $record_number) {}
function dbase_get_record($dbase_identifier, $record_number) {}
function dbase_numrecords($dbase_identifier) {}
function dbase_open($filename, $mode) {}
function dbase_get_record_with_names($dbase_identifier, $record_number) {}
function dbase_numfields($dbase_identifier) {}
function dbase_get_header_info($dbase_identifier) {}
function rar_open($filename, $password) {}
function rar_entry_get($rar_file, $entry_name) {}
function rar_close($rar_file) {}
function rar_list($rar_file) {}
function dom_import_simplexml($node) {}
function bind_textdomain_codeset($domain, $codeset) {}
function dngettext($domain, $msgid1, $msgid2, $n) {}
function dcngettext($domain, $msgid1, $msgid2, $n, $category) {}
function ngettext($msgid1, $msgid2, $n) {}
function dcgettext($domain, $message, $category) {}
function gettext($message) {}
function dgettext($domain, $message) {}
function textdomain($text_domain) {}
function bindtextdomain($domain, $directory) {}
function recode_string($request, $string) {}
function recode_file($request, $input, $output) {}
function http_get_request_headers() {}
function http_match_etag($etag, $for_range = FALSE) {}
function http_get_request_body_stream() {}
function http_support($feature = 0) {}
function http_date($timestamp) {}
function http_match_request_header($header, $value, $match_case = FALSE) {}
function http_get_request_body() {}
function http_build_cookie($cookie) {}
function http_match_modified($timestamp, $for_range = FALSE) {}
function http_negotiate_content_type($supported, $result) {}
function http_negotiate_charset($supported, $result) {}
function http_negotiate_language($supported, $result) {}
function ob_deflatehandler($data, $mode) {}
function ob_inflatehandler($data, $mode) {}
function ob_etaghandler($data, $mode) {}
function http_cache_last_modified($timestamp_or_expires) {}
function http_cache_etag($etag) {}
function http_request_body_encode($fields, $files) {}
function http_put_data($url, $data, $options, $info) {}
function http_get($url, $options, $info) {}
function http_post_data($url, $data, $options, $info) {}
function http_put_stream($url, $stream, $options, $info) {}
function http_request($method, $url, $body, $options, $info) {}
function http_post_fields($url, $data, $files, $options, $info) {}
function http_request_method_name($method) {}
function http_request_method_exists($method) {}
function http_request_method_unregister($method) {}
function http_request_method_register($method) {}
function http_put_file($url, $file, $options, $info) {}
function http_head($url, $options, $info) {}
function http_persistent_handles_count() {}
function http_persistent_handles_clean($ident) {}
function http_persistent_handles_ident($ident) {}
function http_parse_params($param, $flags = HTTP_PARAMS_DEFAULT) {}
function http_parse_cookie($cookie, $flags, $allowed_extras) {}
function http_parse_headers($header) {}
function http_parse_message($message) {}
function http_build_url($url, $parts, $flags = HTTP_URL_REPLACE, $new_url) {}
function http_build_str($query, $prefix, $arg_separator) {}
function http_send_stream($stream) {}
function http_throttle($sec, $bytes = 40960) {}
function http_send_last_modified($timestamp) {}
function http_send_status($status) {}
function http_send_content_disposition($filename, $inline = FALSE) {}
function http_send_file($file) {}
function http_send_data($data) {}
function http_redirect($url, $params, $session = FALSE, $status) {}
function http_send_content_type($content_type = 'applicationxoctetstream') {}
function http_inflate($data) {}
function http_chunked_decode($encoded) {}
function http_deflate($data, $flags = 0) {}
function gnupg_verify($identifier, $signed_text, $signature, $plaintext) {}
function gnupg_getprotocol($identifier) {}
function gnupg_cleardecryptkeys($identifier) {}
function gnupg_decryptverify($identifier, $text, $plaintext) {}
function gnupg_encrypt($identifier, $plaintext) {}
function gnupg_export($identifier, $fingerprint) {}
function gnupg_keyinfo($identifier, $pattern) {}
function gnupg_import($identifier, $keydata) {}
function gnupg_clearsignkeys($identifier) {}
function gnupg_seterrormode($identifier, $errormode) {}
function gnupg_adddecryptkey($identifier, $fingerprint, $passphrase) {}
function gnupg_addencryptkey($identifier, $fingerprint) {}
function gnupg_init() {}
function gnupg_addsignkey($identifier, $fingerprint, $passphrase) {}
function gnupg_geterror($identifier) {}
function gnupg_setsignmode($identifier, $signmode) {}
function gnupg_clearencryptkeys($identifier) {}
function gnupg_sign($identifier, $plaintext) {}
function gnupg_setarmor($identifier, $armor) {}
function gnupg_decrypt($identifier, $text) {}
function gnupg_encryptsign($identifier, $plaintext) {}
function mail($to, $subject, $message, $additional_headers, $additional_parameters) {}
function ezmlm_hash($addr) {}
function pspell_new($language, $spelling, $jargon, $encoding, $mode) {}
function pspell_add_to_personal($dictionary_link, $word) {}
function pspell_config_dict_dir($conf, $directory) {}
function pspell_save_wordlist($dictionary_link) {}
function pspell_config_save_repl($dictionary_link, $flag) {}
function pspell_new_config($config) {}
function pspell_suggest($dictionary_link, $word) {}
function pspell_clear_session($dictionary_link) {}
function pspell_config_ignore($dictionary_link, $n) {}
function pspell_config_personal($dictionary_link, $file) {}
function pspell_add_to_session($dictionary_link, $word) {}
function pspell_config_runtogether($dictionary_link, $flag) {}
function pspell_config_repl($dictionary_link, $file) {}
function pspell_config_data_dir($conf, $directory) {}
function pspell_store_replacement($dictionary_link, $misspelled, $correct) {}
function pspell_config_create($language, $spelling, $jargon, $encoding) {}
function pspell_config_mode($dictionary_link, $mode) {}
function pspell_new_personal($personal, $language, $spelling, $jargon, $encoding, $mode) {}
function pspell_check($dictionary_link, $word) {}
function uksort($array, $cmp_function) {}
function array_intersect_ukey($array1, $array2, $key_compare_func) {}
function array_merge($array1, $array2) {}
function array_uintersect_uassoc($array1, $array2, $data_compare_func, $key_compare_func) {}
function array_search($needle, $haystack, $strict) {}
function natcasesort($array) {}
function array_merge_recursive($array1) {}
function array_sum($array) {}
function compact($varname) {}
function array_walk_recursive($input, $funcname, $userdata) {}
function array_diff_uassoc($array1, $array2, $key_compare_func) {}
function array_map($callback, $arr1) {}
function array_fill($start_index, $num, $value) {}
function in_array($needle, $haystack, $strict) {}
function array_rand($input, $num_req) {}
function array_pop($array) {}
function array_diff($array1, $array2) {}
function next($array) {}
function array_diff_key($array1, $array2) {}
function array_splice($input, $offset, $length, $replacement) {}
function array_count_values($input) {}
function array_chunk($input, $size, $preserve_keys) {}
function array_diff_assoc($array1, $array2) {}
function array_uintersect($array1, $array2, $data_compare_func) {}
function array_key_exists($key, $search) {}
function array_unshift($array, $var) {}
function array_intersect($array1, $array2) {}
function array_udiff($array1, $array2, $data_compare_func) {}
function array_pad($input, $pad_size, $pad_value) {}
function key($array) {}
function array_combine($keys, $values) {}
function end($array) {}
function array_change_key_case($input, $case) {}
function array_intersect_assoc($array1, $array2) {}
function array_shift($array) {}
function ksort($array, $sort_flags) {}
function array_product($array) {}
function reset($array) {}
function array_udiff_assoc($array1, $array2, $data_compare_func) {}
function rsort($array, $sort_flags) {}
function usort($array, $cmp_function) {}
function array_push($array, $var) {}
function array_walk($array, $funcname, $userdata) {}
function array_intersect_uassoc($array1, $array2, $key_compare_func) {}
function extract($var_array, $extract_type, $prefix) {}
function prev($array) {}
function range($low, $high, $step) {}
function array_unique($array) {}
function array_diff_ukey($array1, $array2, $key_compare_func) {}
function each($array) {}
function array_reverse($array, $preserve_keys) {}
function uasort($array, $cmp_function) {}
function array_keys($input, $search_value, $strict) {}
function asort($array, $sort_flags) {}
function array_reduce($input, $function, $initial) {}
function arsort($array, $sort_flags) {}
function array_flip($trans) {}
function array_intersect_key($array1, $array2) {}
function shuffle($array) {}
function krsort($array, $sort_flags) {}
function array_slice($array, $offset, $length, $preserve_keys) {}
function array_filter($input, $callback) {}
function array_uintersect_assoc($array1, $array2, $data_compare_func) {}
function sort($array, $sort_flags) {}
function array_multisort($arr, $arg) {}
function array_values($input) {}
function natsort($array) {}
function array_udiff_uassoc($array1, $array2, $data_compare_func, $key_compare_func) {}
function array_fill_keys($keys, $value) {}
function current($array) {}
function count($var, $mode) {}
function gmp_powm($base, $exp, $mod) {}
function gmp_testbit($a, $index) {}
function gmp_cmp($a, $b) {}
function gmp_nextprime($a) {}
function gmp_invert($a, $b) {}
function gmp_fact($a) {}
function gmp_mod($n, $d) {}
function gmp_init($number, $base) {}
function gmp_xor($a, $b) {}
function gmp_div_qr($n, $d, $round) {}
function gmp_popcount($a) {}
function gmp_mul($a, $b) {}
function gmp_pow($base, $exp) {}
function gmp_div_q($a, $b, $round) {}
function gmp_add($a, $b) {}
function gmp_perfect_square($a) {}
function gmp_jacobi($a, $p) {}
function gmp_div_r($n, $d, $round) {}
function gmp_com($a) {}
function gmp_clrbit($a, $index) {}
function gmp_legendre($a, $p) {}
function gmp_sub($a, $b) {}
function gmp_hamdist($a, $b) {}
function gmp_setbit($a, $index, $set_clear) {}
function gmp_abs($a) {}
function gmp_strval($gmpnumber, $base) {}
function gmp_sign($a) {}
function gmp_scan1($a, $start) {}
function gmp_random($limiter) {}
function gmp_intval($gmpnumber) {}
function gmp_and($a, $b) {}
function gmp_sqrtrem($a) {}
function gmp_prob_prime($a, $reps) {}
function gmp_gcd($a, $b) {}
function gmp_neg($a) {}
function gmp_sqrt($a) {}
function gmp_gcdext($a, $b) {}
function gmp_divexact($n, $d) {}
function gmp_or($a, $b) {}
function gmp_scan0($a, $start) {}
function parsekit_compile_file($filename, $errors, $options) {}
function parsekit_func_arginfo($function) {}
function parsekit_compile_string($phpcode, $errors, $options) {}
function xdiff_string_bdiff($old_data, $new_data) {}
function xdiff_file_merge3($old_file, $new_file1, $new_file2, $dest) {}
function xdiff_file_diff($old_file, $new_file, $dest, $context, $minimal) {}
function xdiff_file_patch($file, $patch, $dest, $flags) {}
function xdiff_string_bpatch($str, $patch) {}
function xdiff_file_bdiff_size($file) {}
function xdiff_file_rabdiff($old_file, $new_file, $dest) {}
function xdiff_string_patch_binary($str, $patch) {}
function xdiff_file_bdiff($old_file, $new_file, $dest) {}
function xdiff_file_patch_binary($file, $patch, $dest) {}
function xdiff_string_diff($old_data, $new_data, $context, $minimal) {}
function xdiff_string_merge3($old_data, $new_data1, $new_data2, $error) {}
function xdiff_file_diff_binary($old_file, $new_file, $dest) {}
function xdiff_string_bdiff_size($patch) {}
function xdiff_string_patch($str, $patch, $flags, $error) {}
function xdiff_file_bpatch($file, $patch, $dest) {}
function xslt_set_base($xh, $uri) {}
function xslt_set_scheme_handler($xh, $handlers) {}
function xslt_set_object($processor, $obj) {}
function xslt_set_log($xh, $log) {}
function xslt_backend_name() {}
function xslt_setopt($processor, $newmask) {}
function xslt_process($xh, $xmlcontainer, $xslcontainer, $resultcontainer, $arguments, $parameters) {}
function xslt_errno($xh) {}
function xslt_backend_version() {}
function xslt_set_sax_handler($xh, $handlers) {}
function xslt_free($xh) {}
function xslt_backend_info() {}
function xslt_error($xh) {}
function xslt_getopt($processor) {}
function xslt_set_sax_handlers($processor, $handlers) {}
function xslt_set_error_handler($xh, $handler) {}
function xslt_set_scheme_handlers($xh, $handlers) {}
function xslt_create() {}
function xslt_set_encoding($xh, $encoding) {}
function odbc_field_scale($result_id, $field_number) {}
function odbc_errormsg($connection_id) {}
function odbc_pconnect($dsn, $user, $password, $cursor_type) {}
function odbc_field_len($result_id, $field_number) {}
function odbc_fetch_row($result_id, $row_number) {}
function odbc_procedures($connection_id) {}
function odbc_field_name($result_id, $field_number) {}
function odbc_close($connection_id) {}
function odbc_columns($connection_id, $qualifier, $schema, $table_name, $column_name) {}
function odbc_exec($connection_id, $query_string, $flags) {}
function odbc_fetch_object($result, $rownumber) {}
function odbc_specialcolumns($connection_id, $type, $qualifier, $owner, $table, $scope, $nullable) {}
function odbc_fetch_into($result_id, $result_array, $rownumber) {}
function odbc_autocommit($connection_id, $OnOff) {}
function odbc_rollback($connection_id) {}
function odbc_num_fields($result_id) {}
function odbc_free_result($result_id) {}
function odbc_fetch_array($result, $rownumber) {}
function odbc_setoption($id, $function, $option, $param) {}
function odbc_error($connection_id) {}
function odbc_statistics($connection_id, $qualifier, $owner, $table_name, $unique, $accuracy) {}
function odbc_tables($connection_id, $qualifier, $owner, $name, $types) {}
function odbc_commit($connection_id) {}
function odbc_longreadlen($result_id, $length) {}
function odbc_num_rows($result_id) {}
function odbc_next_result($result_id) {}
function odbc_execute($result_id, $parameters_array) {}
function odbc_procedurecolumns($connection_id) {}
function odbc_connect($dsn, $user, $password, $cursor_type) {}
function odbc_cursor($result_id) {}
function odbc_foreignkeys($connection_id, $pk_qualifier, $pk_owner, $pk_table, $fk_qualifier, $fk_owner, $fk_table) {}
function odbc_primarykeys($connection_id, $qualifier, $owner, $table) {}
function odbc_result_all($result_id, $format) {}
function odbc_binmode($result_id, $mode) {}
function odbc_tableprivileges($connection_id, $qualifier, $owner, $name) {}
function odbc_field_type($result_id, $field_number) {}
function odbc_gettypeinfo($connection_id, $data_type) {}
function odbc_close_all() {}
function odbc_data_source($connection_id, $fetch_type) {}
function odbc_prepare($connection_id, $query_string) {}
function odbc_columnprivileges($connection_id, $qualifier, $owner, $table_name, $column_name) {}
function odbc_result($result_id, $field) {}
function odbc_field_num($result_id, $field_name) {}
function settype($var, $type) {}
function strval($var) {}
function var_export($expression, $return) {}
function intval($var, $base) {}
function get_defined_vars() {}
function is_buffer($var) {}
function is_array($var) {}
function floatval($var) {}
function is_binary($var) {}
function is_callable($var, $syntax_only, $callable_name) {}
function serialize($value) {}
function debug_zval_dump($variable) {}
function unserialize($str) {}
function gettype($var) {}
function is_null($var) {}
function is_scalar($var) {}
function is_float($var) {}
function is_string($var) {}
function is_object($var) {}
function is_unicode($var) {}
function is_int($var) {}
function is_resource($var) {}
function import_request_variables($types, $prefix) {}
function is_numeric($var) {}
function get_resource_type($handle) {}
function is_bool($var) {}
function var_dump($expression, $expression) {}
function print_r($expression, $return) {}
function oci_new_collection($connection, $tdo, $schema) {}
function oci_new_descriptor($connection, $type) {}
function oci_error($source) {}
function oci_set_prefetch($statement, $rows) {}
function oci_fetch($statement) {}
function oci_fetch_all($statement, $output, $skip, $maxrows, $flags) {}
function oci_new_connect($username, $password, $db, $charset, $session_mode) {}
function oci_field_name($statement, $field) {}
function oci_execute($statement, $mode) {}
function oci_fetch_assoc($statement) {}
function oci_statement_type($statement) {}
function oci_result($statement, $field) {}
function oci_free_statement($statement) {}
function oci_num_rows($statement) {}
function oci_cancel($statement) {}
function oci_field_type_raw($statement, $field) {}
function oci_field_size($statement, $field) {}
function oci_pconnect($username, $password, $db, $charset, $session_mode) {}
function oci_lob_is_equal($lob1, $lob2) {}
function oci_define_by_name($statement, $column_name, $variable, $type) {}
function oci_internal_debug($onoff) {}
function oci_field_scale($statement, $field) {}
function oci_field_is_null($statement, $field) {}
function oci_commit($connection) {}
function oci_fetch_array($statement, $mode) {}
function oci_fetch_row($statement) {}
function oci_new_cursor($connection) {}
function ocifetchinto($statement, $result, $mode) {}
function oci_fetch_object($statement) {}
function oci_close($connection) {}
function oci_server_version($connection) {}
function oci_password_change($connection, $username, $old_password, $new_password) {}
function oci_num_fields($statement) {}
function oci_rollback($connection) {}
function oci_lob_copy($lob_to, $lob_from, $length) {}
function oci_field_precision($statement, $field) {}
function oci_connect($username, $password, $db, $charset, $session_mode) {}
function oci_bind_by_name($statement, $ph_name, $variable, $maxlength, $type) {}
function oci_bind_array_by_name($statement, $name, $var_array, $max_table_length, $max_item_length, $type) {}
function oci_parse($connection, $query) {}
function oci_field_type($statement, $field) {}
function ifx_get_blob($bid) {}
function ifx_textasvarchar($mode) {}
function ifx_fieldproperties($result_id) {}
function ifx_fetch_row($result_id, $position) {}
function ifxus_create_slob($mode) {}
function ifx_copy_blob($bid) {}
function ifx_do($result_id) {}
function ifx_htmltbl_result($result_id, $html_table_options) {}
function ifx_close($link_identifier) {}
function ifxus_read_slob($bid, $nbytes) {}
function ifx_create_blob($type, $mode, $param) {}
function ifx_nullformat($mode) {}
function ifx_free_blob($bid) {}
function ifxus_seek_slob($bid, $mode, $offset) {}
function ifx_connect($database, $userid, $password) {}
function ifxus_free_slob($bid) {}
function ifx_update_blob($bid, $content) {}
function ifx_pconnect($database, $userid, $password) {}
function ifx_get_char($bid) {}
function ifx_prepare($query, $link_identifier, $cursor_def, $blobidarray) {}
function ifx_errormsg($errorcode) {}
function ifxus_write_slob($bid, $content) {}
function ifx_query($query, $link_identifier, $cursor_type, $blobidarray) {}
function ifx_update_char($bid, $content) {}
function ifx_free_result($result_id) {}
function ifxus_open_slob($bid, $mode) {}
function ifx_num_fields($result_id) {}
function ifx_free_char($bid) {}
function ifx_getsqlca($result_id) {}
function ifx_fieldtypes($result_id) {}
function ifxus_close_slob($bid) {}
function ifx_create_char($param) {}
function ifx_num_rows($result_id) {}
function ifx_blobinfile_mode($mode) {}
function ifx_affected_rows($result_id) {}
function ifxus_tell_slob($bid) {}
function ifx_byteasvarchar($mode) {}
function ifx_error($link_identifier) {}
function nthmac($clent, $data) {}
function calculhmac($clent, $data) {}
function calcul_hmac($clent, $siretcode, $price, $reference, $validity, $taxation, $devise, $language) {}
function m_responsekeys($conn, $identifier) {}
function m_transactionssent($conn) {}
function m_monitor($conn) {}
function m_transsend($conn, $identifier) {}
function m_getcommadelimited($conn, $identifier) {}
function m_parsecommadelimited($conn, $identifier) {}
function m_setssl($conn, $host, $port) {}
function m_uwait($microsecs) {}
function m_getcellbynum($conn, $identifier, $column, $row) {}
function m_responseparam($conn, $identifier, $key) {}
function m_setblocking($conn, $tf) {}
function m_getheader($conn, $identifier, $column_num) {}
function m_setssl_files($conn, $sslkeyfile, $sslcertfile) {}
function m_numcolumns($conn, $identifier) {}
function m_initengine($location) {}
function m_verifysslcert($conn, $tf) {}
function m_setip($conn, $host, $port) {}
function m_connectionerror($conn) {}
function m_completeauthorizations($conn, $array) {}
function m_returnstatus($conn, $identifier) {}
function m_deletetrans($conn, $identifier) {}
function m_verifyconnection($conn, $tf) {}
function m_transnew($conn) {}
function m_checkstatus($conn, $identifier) {}
function m_connect($conn) {}
function m_setssl_cafile($conn, $cafile) {}
function m_destroyconn($conn) {}
function m_numrows($conn, $identifier) {}
function m_setdropfile($conn, $directory) {}
function m_getcell($conn, $identifier, $column, $row) {}
function m_transinqueue($conn) {}
function m_initconn() {}
function m_settimeout($conn, $seconds) {}
function m_transkeyval($conn, $identifier, $key, $value) {}
function m_validateidentifier($conn, $tf) {}
function m_iscommadelimited($conn, $identifier) {}
function m_sslcert_gen_hash($filename) {}
function m_maxconntimeout($conn, $secs) {}
function m_destroyengine() {}
function java_last_exception_get() {}
function java_last_exception_clear() {}
function xmlwriter_start_comment($xmlwriter) {}
function xmlwriter_set_indent($xmlwriter, $indent) {}
function xmlwriter_write_dtd_entity($xmlwriter, $name, $content) {}
function xmlwriter_start_cdata($xmlwriter) {}
function xmlwriter_start_attribute($xmlwriter, $name) {}
function xmlwriter_end_attribute($xmlwriter) {}
function xmlwriter_end_pi($xmlwriter) {}
function xmlwriter_write_dtd_element($xmlwriter, $name, $content) {}
function xmlwriter_full_end_element($xmlwriter) {}
function xmlwriter_end_element($xmlwriter) {}
function xmlwriter_start_dtd($xmlwriter, $qualifiedName, $publicId, $systemId) {}
function xmlwriter_end_dtd_entity($xmlwriter) {}
function xmlwriter_write_raw($xmlwriter, $content) {}
function xmlwriter_open_uri($uri) {}
function xmlwriter_end_comment($xmlwriter) {}
function xmlwriter_write_element_ns($xmlwriter, $prefix, $name, $uri, $content) {}
function xmlwriter_end_dtd($xmlwriter) {}
function xmlwriter_write_element($xmlwriter, $name, $content) {}
function xmlwriter_output_memory($xmlwriter, $flush) {}
function xmlwriter_write_attribute($xmlwriter, $name, $value) {}
function xmlwriter_start_dtd_entity($xmlwriter, $name, $isparam) {}
function xmlwriter_write_pi($xmlwriter, $target, $content) {}
function xmlwriter_start_document($xmlwriter, $version, $encoding, $standalone) {}
function xmlwriter_write_attribute_ns($xmlwriter, $prefix, $name, $uri, $content) {}
function xmlwriter_write_comment($xmlwriter, $content) {}
function xmlwriter_end_document($xmlwriter) {}
function xmlwriter_start_attribute_ns($xmlwriter, $prefix, $name, $uri) {}
function xmlwriter_start_element($xmlwriter, $name) {}
function xmlwriter_start_pi($xmlwriter, $target) {}
function xmlwriter_write_cdata($xmlwriter, $content) {}
function xmlwriter_end_dtd_attlist($xmlwriter) {}
function xmlwriter_flush($xmlwriter, $empty) {}
function xmlwriter_write_dtd($xmlwriter, $name, $publicId, $systemId, $subset) {}
function xmlwriter_set_indent_string($xmlwriter, $indentString) {}
function xmlwriter_text($xmlwriter, $content) {}
function xmlwriter_start_element_ns($xmlwriter, $prefix, $name, $uri) {}
function xmlwriter_start_dtd_element($xmlwriter, $qualifiedName) {}
function xmlwriter_start_dtd_attlist($xmlwriter, $name) {}
function xmlwriter_end_dtd_element($xmlwriter) {}
function xmlwriter_open_memory() {}
function xmlwriter_end_cdata($xmlwriter) {}
function xmlwriter_write_dtd_attlist($xmlwriter, $name, $content) {}
function preg_quote($str, $delimiter) {}
function preg_replace_callback($pattern, $callback, $subject, $limit, $count) {}
function preg_last_error() {}
function preg_split($pattern, $subject, $limit, $flags) {}
function preg_replace($pattern, $replacement, $subject, $limit, $count) {}
function preg_grep($pattern, $input, $flags) {}
function preg_match($pattern, $subject, $matches, $flags, $offset) {}
function preg_match_all($pattern, $subject, $matches, $flags, $offset) {}
function hw_inscoll($connection, $objectID, $object_array) {}
function hw_output_document($hw_document) {}
function hw_mapid($connection, $server_id, $object_id) {}
function hw_root() {}
function hw_edittext($connection, $hw_document) {}
function hw_dummy($link, $id, $msgid) {}
function hw_free_document($hw_document) {}
function hw_gettext($connection, $objectID, $rootIDprefix) {}
function hw_getchilddoccoll($connection, $objectID) {}
function hw_connection_info($link) {}
function hw_getobjectbyquerycoll($connection, $objectID, $query, $max_hits) {}
function hw_insertobject($connection, $object_rec, $parameter) {}
function hw_modifyobject($connection, $object_to_change, $remove, $add, $mode) {}
function hw_array2objrec($object_array) {}
function hw_getchilddoccollobj($connection, $objectID) {}
function hw_document_content($hw_document) {}
function hw_insertanchors($hwdoc, $anchorecs, $dest, $urlprefixes) {}
function hw_getobjectbyqueryobj($connection, $query, $max_hits) {}
function hw_docbyanchorobj($connection, $anchorID) {}
function hw_getrellink($link, $rootid, $sourceid, $destid) {}
function hw_getobjectbyquerycollobj($connection, $objectID, $query, $max_hits) {}
function hw_insertdocument($connection, $parent_id, $hw_document) {}
function hw_getusername($connection) {}
function hw_new_document($object_record, $document_data, $document_size) {}
function hw_getremote($connection, $objectID) {}
function hw_stat($link) {}
function hw_getobjectbyquery($connection, $query, $max_hits) {}
function hw_mv($connection, $object_id_array, $source_id, $destination_id) {}
function hw_getanchors($connection, $objectID) {}
function hw_who($connection) {}
function hw_document_size($hw_document) {}
function hw_errormsg($connection) {}
function hw_pipedocument($connection, $objectID, $url_prefixes) {}
function hw_getparentsobj($connection, $objectID) {}
function hw_cp($connection, $object_id_array, $destination_id) {}
function hw_identify($link, $username, $password) {}
function hw_document_setcontent($hw_document, $content) {}
function hw_deleteobject($connection, $object_to_delete) {}
function hw_getparents($connection, $objectID) {}
function hw_objrec2array($object_record, $format) {}
function hw_document_bodytag($hw_document, $prefix) {}
function hw_docbyanchor($connection, $anchorID) {}
function hw_info($connection) {}
function hw_pconnect($host, $port, $username, $password) {}
function hw_changeobject($link, $objid, $attributes) {}
function hw_error($connection) {}
function hw_getremotechildren($connection, $object_record) {}
function hw_getchildcollobj($connection, $objectID) {}
function hw_close($connection) {}
function hw_children($connection, $objectID) {}
function hw_getanchorsobj($connection, $objectID) {}
function hw_unlock($connection, $objectID) {}
function hw_getobject($connection, $objectID, $query) {}
function hw_connect($host, $port, $username, $password) {}
function hw_getandlock($connection, $objectID) {}
function hw_insdoc($connection, $parentID, $object_record, $text) {}
function hw_incollections($connection, $object_id_array, $collection_id_array, $return_collections) {}
function hw_getsrcbydestobj($connection, $objectID) {}
function hw_document_attributes($hw_document) {}
function hw_getchildcoll($connection, $objectID) {}
function hw_childrenobj($connection, $objectID) {}
function hw_setlinkroot($link, $rootid) {}
function ingres_errsqlstate($link) {}
function ingres_field_type($index, $link) {}
function ingres_num_rows($link) {}
function ingres_field_length($index, $link) {}
function ingres_commit($link) {}
function ingres_field_nullable($index, $link) {}
function ingres_connect($database, $username, $password, $options) {}
function ingres_field_scale($index, $link) {}
function ingres_errno($link) {}
function ingres_fetch_row($link) {}
function ingres_error($link) {}
function ingres_query($query, $link) {}
function ingres_fetch_array($result_type, $link) {}
function ingres_field_name($index, $link) {}
function ingres_field_precision($index, $link) {}
function ingres_num_fields($link) {}
function ingres_autocommit($link) {}
function ingres_fetch_object($result_type, $link) {}
function ingres_rollback($link) {}
function ingres_cursor($link) {}
function ingres_pconnect($database, $username, $password) {}
function ingres_close($link) {}
function swf_actiongotolabel($label) {}
function swf_startbutton($objid, $type) {}
function swf_getfontinfo() {}
function swf_showframe() {}
function swf_fontslant($slant) {}
function swf_fonttracking($tracking) {}
function swf_addbuttonrecord($states, $shapeid, $depth) {}
function swf_shapefillsolid($r, $g, $b, $a) {}
function swf_ortho($xmin, $xmax, $ymin, $ymax, $zmin, $zmax) {}
function swf_actionprevframe() {}
function swf_rotate($angle, $axis) {}
function swf_modifyobject($depth, $how) {}
function swf_viewport($xmin, $xmax, $ymin, $ymax) {}
function swf_setframe($framenumber) {}
function swf_definebitmap($objid, $image_name) {}
function swf_startsymbol($objid) {}
function swf_shapearc($x, $y, $r, $ang1, $ang2) {}
function swf_shapefillbitmapclip($bitmapid) {}
function swf_defineline($objid, $x1, $y1, $x2, $y2, $width) {}
function swf_labelframe($name) {}
function swf_actionnextframe() {}
function swf_actiongotoframe($framenumber) {}
function swf_popmatrix() {}
function swf_closefile($return_file) {}
function swf_translate($x, $y, $z) {}
function swf_getbitmapinfo($bitmapid) {}
function swf_ortho2($xmin, $xmax, $ymin, $ymax) {}
function swf_definepoly($objid, $coords, $npoints, $width) {}
function swf_shapelineto($x, $y) {}
function swf_getframe() {}
function swf_actionstop() {}
function swf_mulcolor($r, $g, $b, $a) {}
function swf_shapefillbitmaptile($bitmapid) {}
function swf_definefont($fontid, $fontname) {}
function swf_nextid() {}
function swf_definerect($objid, $x1, $y1, $x2, $y2, $width) {}
function swf_shapemoveto($x, $y) {}
function swf_shapecurveto($x1, $y1, $x2, $y2) {}
function swf_definetext($objid, $str, $docenter) {}
function swf_endbutton() {}
function swf_textwidth($str) {}
function swf_startdoaction() {}
function swf_perspective($fovy, $aspect, $near, $far) {}
function swf_posround($round) {}
function swf_shapecurveto3($x1, $y1, $x2, $y2, $x3, $y3) {}
function swf_removeobject($depth) {}
function swf_fontsize($size) {}
function swf_addcolor($r, $g, $b, $a) {}
function swf_shapelinesolid($r, $g, $b, $a, $width) {}
function swf_openfile($filename, $width, $height, $framerate, $r, $g, $b) {}
function swf_endsymbol() {}
function swf_endshape() {}
function swf_pushmatrix() {}
function swf_actiontogglequality() {}
function swf_actiongeturl($url, $target) {}
function swf_placeobject($objid, $depth) {}
function swf_enddoaction() {}
function swf_actionwaitforframe($framenumber, $skipcount) {}
function swf_lookat($view_x, $view_y, $view_z, $reference_x, $reference_y, $reference_z, $twist) {}
function swf_oncondition($transition) {}
function swf_shapefilloff() {}
function swf_actionplay() {}
function swf_actionsettarget($target) {}
function swf_polarview($dist, $azimuth, $incidence, $twist) {}
function swf_scale($x, $y, $z) {}
function swf_startshape($objid) {}
function swf_setfont($fontid) {}
function pcntl_getpriority($pid, $process_identifier) {}
function pcntl_fork() {}
function pcntl_wstopsig($status) {}
function pcntl_wifexited($status) {}
function pcntl_setpriority($priority, $pid, $process_identifier) {}
function pcntl_exec($path, $args, $envs) {}
function pcntl_waitpid($pid, $status, $options) {}
function pcntl_signal($signo, $handler, $restart_syscalls) {}
function pcntl_wifstopped($status) {}
function pcntl_wexitstatus($status) {}
function pcntl_wtermsig($status) {}
function pcntl_wait($status, $options) {}
function pcntl_wifsignaled($status) {}
function pcntl_alarm($seconds) {}
function yp_order($domain, $map) {}
function yp_master($domain, $map) {}
function yp_first($domain, $map) {}
function yp_all($domain, $map, $callback) {}
function yp_match($domain, $map, $key) {}
function yp_errno() {}
function yp_err_string($errorcode) {}
function yp_cat($domain, $map) {}
function yp_next($domain, $map, $key) {}
function yp_get_default_domain() {}
function printer_create_pen($style, $width, $color) {}
function printer_delete_font($font_handle) {}
function printer_draw_chord($printer_handle, $rec_x, $rec_y, $rec_x1, $rec_y1, $rad_x, $rad_y, $rad_x1, $rad_y1) {}
function printer_draw_elipse($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y) {}
function printer_delete_pen($pen_handle) {}
function printer_draw_bmp($printer_handle, $filename, $x, $y, $width, $height) {}
function printer_draw_pie($printer_handle, $rec_x, $rec_y, $rec_x1, $rec_y1, $rad1_x, $rad1_y, $rad2_x, $rad2_y) {}
function printer_delete_brush($brush_handle) {}
function printer_select_pen($printer_handle, $pen_handle) {}
function printer_select_brush($printer_handle, $brush_handle) {}
function printer_list($enumtype, $name, $level) {}
function printer_select_font($printer_handle, $font_handle) {}
function printer_open($printername) {}
function printer_abort($printer_handle) {}
function printer_create_dc($printer_handle) {}
function printer_create_font($face, $height, $width, $font_weight, $italic, $underline, $strikeout, $orientation) {}
function printer_delete_dc($printer_handle) {}
function printer_get_option($printer_handle, $option) {}
function printer_close($printer_handle) {}
function printer_end_doc($printer_handle) {}
function printer_draw_text($printer_handle, $text, $x, $y) {}
function printer_start_doc($printer_handle, $document) {}
function printer_create_brush($style, $color) {}
function printer_set_option($printer_handle, $option, $value) {}
function printer_start_page($printer_handle) {}
function printer_write($printer_handle, $content) {}
function printer_logical_fontheight($printer_handle, $height) {}
function printer_draw_line($printer_handle, $from_x, $from_y, $to_x, $to_y) {}
function printer_draw_roundrect($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y, $width, $height) {}
function printer_draw_rectangle($printer_handle, $ul_x, $ul_y, $lr_x, $lr_y) {}
function printer_end_page($printer_handle) {}
function mysql_field_len($result, $field_offset) {}
function mysql_client_encoding($link_identifier) {}
function mysql_fetch_object($result, $class_name, $params) {}
function mysql_error($link_identifier) {}
function mysql_query($query, $link_identifier) {}
function mysql_thread_id($link_identifier) {}
function mysql_info($link_identifier) {}
function mysql_fetch_array($result, $result_type) {}
function mysql_change_user($user, $password, $database, $link_identifier) {}
function mysql_drop_db($database_name, $link_identifier) {}
function mysql_fetch_field($result, $field_offset) {}
function mysql_free_result($result) {}
function mysql_data_seek($result, $row_number) {}
function mysql_db_query($database, $query, $link_identifier) {}
function mysql_close($link_identifier) {}
function mysql_pconnect($server, $username, $password, $client_flags) {}
function mysql_real_escape_string($unescaped_string, $link_identifier) {}
function mysql_num_fields($result) {}
function mysql_errno($link_identifier) {}
function mysql_tablename($result, $i) {}
function mysql_field_flags($result, $field_offset) {}
function mysql_fetch_lengths($result) {}
function mysql_fetch_assoc($result) {}
function mysql_get_proto_info($link_identifier) {}
function mysql_field_seek($result, $field_offset) {}
function mysql_list_processes($link_identifier) {}
function mysql_field_table($result, $field_offset) {}
function mysql_insert_id($link_identifier) {}
function mysql_create_db($database_name, $link_identifier) {}
function mysql_stat($link_identifier) {}
function mysql_escape_string($unescaped_string) {}
function mysql_unbuffered_query($query, $link_identifier) {}
function mysql_set_charset($charset, $link_identifier) {}
function mysql_fetch_row($result) {}
function mysql_field_type($result, $field_offset) {}
function mysql_num_rows($result) {}
function mysql_field_name($result, $field_offset) {}
function mysql_list_fields($database_name, $table_name, $link_identifier) {}
function mysql_get_server_info($link_identifier) {}
function mysql_affected_rows($link_identifier) {}
function mysql_connect($server, $username, $password, $new_link, $client_flags) {}
function mysql_select_db($database_name, $link_identifier) {}
function mysql_db_name($result, $row, $field) {}
function mysql_ping($link_identifier) {}
function mysql_get_client_info() {}
function mysql_result($result, $row, $field) {}
function mysql_list_dbs($link_identifier) {}
function mysql_get_host_info($link_identifier) {}
function mysql_list_tables($database, $link_identifier) {}
function lchown($filename, $user) {}
function readlink($path) {}
function flock($handle, $operation, $wouldblock) {}
function is_file($filename) {}
function linkinfo($path) {}
function fileowner($filename) {}
function feof($handle) {}
function disk_total_space($directory) {}
function lchgrp($filename, $group) {}
function file_put_contents($filename, $data, $flags, $context) {}
function fflush($handle) {}
function stat($filename) {}
function lstat($filename) {}
function is_readable($filename) {}
function file_get_contents($filename, $flags, $context, $offset, $maxlen) {}
function basename($path, $suffix) {}
function clearstatcache() {}
function fopen($filename, $mode, $use_include_path, $context) {}
function popen($command, $mode) {}
function rename($oldname, $newname, $context) {}
function tmpfile() {}
function filectime($filename) {}
function file($filename, $flags, $context) {}
function fileperms($filename) {}
function filegroup($filename) {}
function copy($source, $dest, $context) {}
function parse_ini_file($filename, $process_sections) {}
function ftell($handle) {}
function fputcsv($handle, $fields, $delimiter, $enclosure) {}
function fileinode($filename) {}
function rewind($handle) {}
function fgets($handle, $length) {}
function chmod($filename, $mode) {}
function fclose($handle) {}
function fstat($handle) {}
function readfile($filename, $use_include_path, $context) {}
function symlink($target, $link) {}
function realpath($path) {}
function fnmatch($pattern, $string, $flags) {}
function umask($mask) {}
function is_writable($filename) {}
function is_dir($filename) {}
function fpassthru($handle) {}
function fread($handle, $length) {}
function file_exists($filename) {}
function fgetcsv($handle, $length, $delimiter, $enclosure, $escape) {}
function link($target, $link) {}
function pathinfo($path, $options) {}
function is_link($filename) {}
function filemtime($filename) {}
function fgetss($handle, $length, $allowable_tags) {}
function ftruncate($handle, $size) {}
function delete() {}
function is_uploaded_file($filename) {}
function fileatime($filename) {}
function pclose($handle) {}
function chown($filename, $user) {}
function chgrp($filename, $group) {}
function tempnam($dir, $prefix) {}
function filesize($filename) {}
function fscanf($handle, $format) {}
function fwrite($handle, $string, $length) {}
function glob($pattern, $flags) {}
function touch($filename, $time, $atime) {}
function dirname($path) {}
function rmdir($dirname, $context) {}
function mkdir($pathname, $mode, $recursive, $context) {}
function filetype($filename) {}
function unlink($filename, $context) {}
function is_executable($filename) {}
function move_uploaded_file($filename, $destination) {}
function fseek($handle, $offset, $whence) {}
function fgetc($handle) {}
function disk_free_space($directory) {}
function openssl_csr_export($csr, $out, $notext) {}
function openssl_csr_get_public_key($csr, $use_shortnames) {}
function openssl_pkcs12_read($PKCS12, $certs, $pass) {}
function openssl_x509_checkpurpose($x509cert, $purpose, $cainfo, $untrustedfile) {}
function openssl_x509_free($x509cert) {}
function openssl_x509_export($x509, $output, $notext) {}
function openssl_public_encrypt($data, $crypted, $key, $padding) {}
function openssl_pkey_export_to_file($key, $outfilename, $passphrase, $configargs) {}
function openssl_pkcs7_sign($infilename, $outfilename, $signcert, $privkey, $headers, $flags, $extracerts) {}
function openssl_pkcs7_decrypt($infilename, $outfilename, $recipcert, $recipkey) {}
function openssl_x509_read($x509certdata) {}
function openssl_pkey_get_details($key) {}
function openssl_public_decrypt($data, $decrypted, $key, $padding) {}
function openssl_sign($data, $signature, $priv_key_id, $signature_alg) {}
function openssl_csr_new($dn, $privkey, $configargs, $extraattribs) {}
function openssl_pkcs12_export($x509, $out, $priv_key, $pass, $args) {}
function openssl_pkey_get_public($certificate) {}
function openssl_x509_parse($x509cert, $shortnames) {}
function openssl_open($sealed_data, $open_data, $env_key, $priv_key_id) {}
function openssl_seal($data, $sealed_data, $env_keys, $pub_key_ids) {}
function openssl_pkey_new($configargs) {}
function openssl_csr_export_to_file($csr, $outfilename, $notext) {}
function openssl_csr_sign($csr, $cacert, $priv_key, $days, $configargs, $serial) {}
function openssl_csr_get_subject($csr, $use_shortnames) {}
function openssl_x509_check_private_key($cert, $key) {}
function openssl_pkcs7_verify($filename, $flags, $outfilename, $cainfo, $extracerts, $content) {}
function openssl_pkey_get_private($key, $passphrase) {}
function openssl_private_decrypt($data, $decrypted, $key, $padding) {}
function openssl_pkcs7_encrypt($infile, $outfile, $recipcerts, $headers, $flags, $cipherid) {}
function openssl_pkcs12_export_to_file($x509, $filename, $priv_key, $pass, $args) {}
function openssl_pkey_free($key) {}
function openssl_verify($data, $signature, $pub_key_id, $signature_alg) {}
function openssl_x509_export_to_file($x509, $outfilename, $notext) {}
function openssl_free_key($key_identifier) {}
function openssl_error_string() {}
function openssl_private_encrypt($data, $crypted, $key, $padding) {}
function openssl_pkey_export($key, $out, $passphrase, $configargs) {}
function px_create_fp($pxdoc, $file, $fielddesc) {}
function px_new() {}
function px_open_fp($pxdoc, $file) {}
function px_get_schema($pxdoc, $mode) {}
function px_get_info($pxdoc) {}
function px_update_record($pxdoc, $data, $num) {}
function px_put_record($pxdoc, $record, $recpos) {}
function px_set_value($pxdoc, $name, $value) {}
function px_set_blob_file($pxdoc, $filename) {}
function px_retrieve_record($pxdoc, $num, $mode) {}
function px_set_parameter($pxdoc, $name, $value) {}
function px_insert_record($pxdoc, $data) {}
function px_get_value($pxdoc, $name) {}
function px_get_field($pxdoc, $fieldno) {}
function px_set_tablename($pxdoc, $name) {}
function px_delete($pxdoc) {}
function px_numrecords($pxdoc) {}
function px_timestamp2string($pxdoc, $value, $format) {}
function px_numfields($pxdoc) {}
function px_set_targetencoding($pxdoc, $encoding) {}
function px_date2string($pxdoc, $value, $format) {}
function px_close($pxdoc) {}
function px_delete_record($pxdoc, $num) {}
function px_get_record($pxdoc, $num, $mode) {}
function px_get_parameter($pxdoc, $name) {}
function qdom_tree($doc) {}
function qdom_error() {}
function openal_source_set($source, $property, $setting) {}
function openal_context_process($context) {}
function openal_device_open($device_desc) {}
function openal_buffer_destroy($buffer) {}
function openal_context_suspend($context) {}
function openal_buffer_get($buffer, $property) {}
function openal_source_rewind($source) {}
function openal_buffer_create() {}
function openal_source_play($source) {}
function openal_buffer_loadwav($buffer, $wavfile) {}
function openal_source_stop($source) {}
function openal_source_get($source, $property) {}
function openal_listener_get($property) {}
function openal_context_destroy($context) {}
function openal_source_pause($source) {}
function openal_context_current($context) {}
function openal_context_create($device) {}
function openal_buffer_data($buffer, $format, $data, $freq) {}
function openal_source_create() {}
function openal_source_destroy($source) {}
function openal_listener_set($property, $setting) {}
function openal_stream($source, $format, $rate) {}
function openal_device_close($device) {}
function stats_harmonic_mean($a) {}
function stats_rand_gen_ibinomial($n, $pp) {}
function stats_kurtosis($a) {}
function stats_stat_noncentral_t($par1, $par2, $par3, $which) {}
function stats_cdf_noncentral_f($par1, $par2, $par3, $par4, $which) {}
function stats_dens_exponential($x, $scale) {}
function stats_cdf_f($par1, $par2, $par3, $which) {}
function stats_stat_independent_t($arr1, $arr2) {}
function stats_cdf_uniform($par1, $par2, $par3, $which) {}
function stats_cdf_laplace($par1, $par2, $par3, $which) {}
function stats_rand_gen_normal($av, $sd) {}
function stats_dens_pmf_poisson($x, $lb) {}
function stats_cdf_chisquare($par1, $par2, $which) {}
function stats_rand_gen_beta($a, $b) {}
function stats_variance($a, $sample) {}
function stats_cdf_binomial($par1, $par2, $par3, $which) {}
function stats_den_uniform($x, $a, $b) {}
function stats_absolute_deviation($a) {}
function stats_cdf_logistic($par1, $par2, $par3, $which) {}
function stats_rand_gen_t($df) {}
function stats_rand_gen_chisquare($df) {}
function stats_stat_binomial_coef($x, $n) {}
function stats_dens_pmf_binomial($x, $n, $pi) {}
function stats_rand_setall($iseed1, $iseed2) {}
function stats_rand_gen_iuniform($low, $high) {}
function stats_rand_gen_funiform($low, $high) {}
function stats_standard_deviation($a, $sample) {}
function stats_dens_beta($x, $a, $b) {}
function stats_rand_gen_exponential($av) {}
function stats_dens_weibull($x, $a, $b) {}
function stats_cdf_noncentral_chisquare($par1, $par2, $par3, $which) {}
function stats_rand_get_seeds() {}
function stats_dens_negative_binomial($x, $n, $pi) {}
function stats_dens_t($x, $dfr) {}
function stats_rand_gen_noncenral_chisquare($df, $xnonc) {}
function stats_cdf_weibull($par1, $par2, $par3, $which) {}
function stats_rand_gen_f($dfn, $dfd) {}
function stats_rand_ranf() {}
function stats_dens_logistic($x, $ave, $stdev) {}
function stats_rand_gen_noncentral_t($df, $xnonc) {}
function stats_dens_cauchy($x, $ave, $stdev) {}
function stats_covariance($a, $b) {}
function stats_stat_paired_t($arr1, $arr2) {}
function stats_dens_laplace($x, $ave, $stdev) {}
function stats_stat_gennch($n) {}
function stats_dens_pmf_hypergeometric($n1, $n2, $N1, $N2) {}
function stats_stat_percentile($df, $xnonc) {}
function stats_dens_f($x, $dfr1, $dfr2) {}
function stats_rand_phrase_to_seeds($phrase) {}
function stats_rand_gen_ibinomial_negative($n, $p) {}
function stats_stat_correlation($arr1, $arr2) {}
function stats_dens_normal($x, $ave, $stdev) {}
function stats_skew($a) {}
function stats_stat_powersum($arr, $power) {}
function stats_rand_gen_ipoisson($mu) {}
function stats_cdf_exponential($par1, $par2, $which) {}
function stats_cdf_cauchy($par1, $par2, $par3, $which) {}
function stats_cdf_gamma($par1, $par2, $par3, $which) {}
function stats_cdf_negative_binomial($par1, $par2, $par3, $which) {}
function stats_dens_gamma($x, $shape, $scale) {}
function stats_cdf_beta($par1, $par2, $par3, $which) {}
function stats_rand_gen_noncentral_f($dfn, $dfd, $xnonc) {}
function stats_cdf_t($par1, $par2, $which) {}
function stats_stat_innerproduct($arr1, $arr2) {}
function stats_rand_gen_gamma($a, $r) {}
function stats_rand_gen_int() {}
function stats_cdf_poisson($par1, $par2, $which) {}
function stats_dens_chisquare($x, $dfr) {}
function lzf_compress($data) {}
function lzf_decompress($data) {}
function lzf_optimized_for() {}
function fbsql_insert_id($link_identifier) {}
function fbsql_db_status($database_name, $link_identifier) {}
function fbsql_list_dbs($link_identifier) {}
function fbsql_stop_db($database_name, $link_identifier) {}
function fbsql_hostname($link_identifier, $host_name) {}
function fbsql_commit($link_identifier) {}
function fbsql_affected_rows($link_identifier) {}
function fbsql_fetch_object($result) {}
function fbsql_field_table($result, $field_offset) {}
function fbsql_errno($link_identifier) {}
function fbsql_create_db($database_name, $link_identifier, $database_options) {}
function fbsql_fetch_row($result) {}
function fbsql_num_fields($result) {}
function fbsql_fetch_field($result, $field_offset) {}
function fbsql_read_blob($blob_handle, $link_identifier) {}
function fbsql_field_flags($result, $field_offset) {}
function fbsql_pconnect($hostname, $username, $password) {}
function fbsql_field_name($result, $field_index) {}
function fbsql_warnings($OnOff) {}
function fbsql_field_len($result, $field_offset) {}
function fbsql_result($result, $row, $field) {}
function fbsql_num_rows($result) {}
function fbsql_list_tables($database, $link_identifier) {}
function fbsql_fetch_lengths($result) {}
function fbsql_rollback($link_identifier) {}
function fbsql_list_fields($database_name, $table_name, $link_identifier) {}
function fbsql_blob_size($blob_handle, $link_identifier) {}
function fbsql_set_transaction($link_identifier, $locking, $isolation) {}
function fbsql_connect($hostname, $username, $password) {}
function fbsql_table_name($result, $index) {}
function fbsql_database($link_identifier, $database) {}
function fbsql_database_password($link_identifier, $database_password) {}
function fbsql_set_password($link_identifier, $user, $password, $old_password) {}
function fbsql_password($link_identifier, $password) {}
function fbsql_free_result($result) {}
function fbsql_start_db($database_name, $link_identifier, $database_options) {}
function fbsql_create_clob($clob_data, $link_identifier) {}
function fbsql_read_clob($clob_handle, $link_identifier) {}
function fbsql_create_blob($blob_data, $link_identifier) {}
function fbsql_clob_size($clob_handle, $link_identifier) {}
function fbsql_error($link_identifier) {}
function fbsql_query($query, $link_identifier, $batch_size) {}
function fbsql_set_lob_mode($result, $lob_mode) {}
function fbsql_autocommit($link_identifier, $OnOff) {}
function fbsql_set_characterset($link_identifier, $characterset, $in_out_both) {}
function fbsql_drop_db($database_name, $link_identifier) {}
function fbsql_data_seek($result, $row_number) {}
function fbsql_db_query($database, $query, $link_identifier) {}
function fbsql_change_user($user, $password, $database, $link_identifier) {}
function fbsql_close($link_identifier) {}
function fbsql_fetch_assoc($result) {}
function fbsql_field_type($result, $field_offset) {}
function fbsql_get_autostart_info($link_identifier) {}
function fbsql_fetch_array($result, $result_type) {}
function fbsql_select_db($database_name, $link_identifier) {}
function fbsql_rows_fetched($result) {}
function fbsql_next_result($result) {}
function fbsql_field_seek($result, $field_offset) {}
function fbsql_username($link_identifier, $username) {}
function id3_get_genre_id($genre) {}
function id3_get_frame_short_name($frameId) {}
function id3_set_tag($filename, $tag, $version) {}
function id3_get_tag($filename, $version) {}
function id3_get_genre_list() {}
function id3_get_frame_long_name($frameId) {}
function id3_get_genre_name($genre_id) {}
function id3_get_version($filename) {}
function id3_remove_tag($filename, $version) {}
function func_num_args() {}
function func_get_arg($arg_num) {}
function function_exists($function_name) {}
function register_tick_function($function, $arg) {}
function call_user_func_array($function, $param_arr) {}
function call_user_func($function, $parameter) {}
function get_defined_functions() {}
function register_shutdown_function($function, $parameter) {}
function unregister_tick_function($function_name) {}
function create_function($args, $code) {}
function func_get_args() {}
function cyrus_authenticate($connection, $mechlist, $service, $user, $minssf, $maxssf, $authname, $password) {}
function cyrus_connect($host, $port, $flags) {}
function cyrus_bind($connection, $callbacks) {}
function cyrus_unbind($connection, $trigger_name) {}
function cyrus_close($connection) {}
function cyrus_query($connection, $query) {}
function overload($class_name) {}
function imap_fetchbody($imap_stream, $msg_number, $part_number, $options) {}
function imap_getsubscribed($imap_stream, $ref, $pattern) {}
function imap_subscribe($imap_stream, $mailbox) {}
function imap_get_quota($imap_stream, $quota_root) {}
function imap_getmailboxes($imap_stream, $ref, $pattern) {}
function imap_ping($imap_stream) {}
function imap_alerts() {}
function imap_utf7_decode($text) {}
function imap_getacl($imap_stream, $mailbox) {}
function imap_8bit($string) {}
function imap_headers($imap_stream) {}
function imap_num_recent($imap_stream) {}
function imap_fetchstructure($imap_stream, $msg_number, $options) {}
function imap_bodystruct($imap_stream, $msg_number, $section) {}
function imap_fetch_overview($imap_stream, $sequence, $options) {}
function imap_uid($imap_stream, $msg_number) {}
function imap_body($imap_stream, $msg_number, $options) {}
function imap_get_quotaroot($imap_stream, $quota_root) {}
function imap_thread($imap_stream, $options) {}
function imap_undelete($imap_stream, $msg_number, $flags) {}
function imap_deletemailbox($imap_stream, $mailbox) {}
function imap_clearflag_full($imap_stream, $sequence, $flag, $options) {}
function imap_list($imap_stream, $ref, $pattern) {}
function imap_renamemailbox($imap_stream, $old_mbox, $new_mbox) {}
function imap_last_error() {}
function imap_headerinfo($imap_stream, $msg_number, $fromlength, $subjectlength, $defaulthost) {}
function imap_append($imap_stream, $mailbox, $message, $options) {}
function imap_msgno($imap_stream, $uid) {}
function imap_delete($imap_stream, $msg_number, $options) {}
function imap_unsubscribe($imap_stream, $mailbox) {}
function imap_mailboxmsginfo($imap_stream) {}
function imap_mail_copy($imap_stream, $msglist, $mailbox, $options) {}
function imap_utf7_encode($data) {}
function imap_lsub($imap_stream, $ref, $pattern) {}
function imap_createmailbox($imap_stream, $mailbox) {}
function imap_set_quota($imap_stream, $quota_root, $quota_limit) {}
function imap_binary($string) {}
function imap_savebody($imap_stream, $file, $msg_number, $part_number, $options) {}
function imap_rfc822_write_address($mailbox, $host, $personal) {}
function imap_utf8($mime_encoded_text) {}
function imap_reopen($imap_stream, $mailbox, $options, $n_retries) {}
function imap_listscan($imap_stream, $ref, $pattern, $content) {}
function imap_search($imap_stream, $criteria, $options, $charset) {}
function imap_rfc822_parse_adrlist($address, $default_host) {}
function imap_errors() {}
function imap_close($imap_stream, $flag) {}
function imap_open($mailbox, $username, $password, $options, $n_retries) {}
function imap_base64($text) {}
function imap_mime_header_decode($text) {}
function imap_fetchheader($imap_stream, $msg_number, $options) {}
function imap_expunge($imap_stream) {}
function imap_timeout($timeout_type, $timeout) {}
function imap_mail_move($imap_stream, $msglist, $mailbox, $options) {}
function imap_mail_compose($envelope, $body) {}
function imap_sort($imap_stream, $criteria, $reverse, $options, $search_criteria, $charset) {}
function imap_setacl($imap_stream, $mailbox, $id, $rights) {}
function imap_setflag_full($imap_stream, $sequence, $flag, $options) {}
function imap_mail($to, $subject, $message, $additional_headers, $cc, $bcc, $rpath) {}
function imap_rfc822_parse_headers($headers, $defaulthost) {}
function imap_num_msg($imap_stream) {}
function imap_check($imap_stream) {}
function imap_status($imap_stream, $mailbox, $options) {}
function imap_qprint($string) {}
function apache_get_modules() {}
function apache_request_headers() {}
function apache_note($note_name, $note_value) {}
function apache_lookup_uri($filename) {}
function ascii2ebcdic($ascii_str) {}
function ebcdic2ascii($ebcdic_str) {}
function virtual($filename) {}
function apache_get_version() {}
function apache_getenv($variable, $walk_to_top) {}
function getallheaders() {}
function apache_reset_timeout() {}
function apache_child_terminate() {}
function apache_response_headers() {}
function apache_setenv($variable, $value, $walk_to_top) {}
function mysqli_enable_reads_from_master($link) {}
function mysqli_rpl_probe($link) {}
function mysqli_report($flags) {}
function mysqli_send_query($link, $query) {}
function mysqli_master_query($link, $query) {}
function mysqli_rpl_query_type($link, $query) {}
function mysqli_slave_query($link, $query) {}
function mysqli_disable_rpl_parse($link) {}
function mysqli_rpl_parse_enabled($link) {}
function mysqli_enable_rpl_parse($link) {}
function mysqli_disable_reads_from_master($link) {}
function mysqli_num_fields($result) {}
function mysqli_field_tell($result) {}
function mysqli_fetch_lengths($result) {}
function mysqli_num_rows($result) {}
function mysqli_field_count($link) {}
function mysqli_connect($host, $username, $passwd, $dbname, $port, $socket) {}
function mysqli_set_local_infile_handler($link, $read_func) {}
function mysqli_stmt_init($link) {}
function mysqli_set_local_infile_default($link) {}
function real_query($query) {}
function mysqli_connect_error() {}
function use_result() {}
function mysqli_sqlstate($link) {}
function prepare($query) {}
function mysqli_insert_id($link) {}
function mysqli_thread_id($link) {}
function mysqli_error($link) {}
function mysqli_affected_rows($link) {}
function mysqli_get_server_version($link) {}
function mysqli_thread_safe() {}
function mysqli_errno($link) {}
function mysqli_get_proto_info($link) {}
function mysqli_get_host_info($link) {}
function init() {}
function mysqli_connect_errno() {}
function mysqli_info($link) {}
function mysqli_get_server_info($link) {}
function store_result() {}
function mysqli_warning_count($link) {}
function mysqli_stmt_field_count($stmt) {}
function mysqli_stmt_attr_set($stmt, $attr, $mode) {}
function mysqli_stmt_attr_get($stmt, $attr) {}
function mysqli_stmt_param_count($stmt) {}
function mysqli_stmt_sqlstate($stmt) {}
function mysqli_stmt_insert_id($stmt) {}
function mysqli_stmt_num_rows($stmt) {}
function mysqli_stmt_error($stmt) {}
function mysqli_stmt_affected_rows($stmt) {}
function mysqli_stmt_errno($stmt) {}
function rpm_get_tag($rpmr, $tagnum) {}
function rpm_is_valid($filename) {}
function rpm_version() {}
function rpm_close($rpmr) {}
function rpm_open($filename) {}
function session_get_cookie_params() {}
function session_destroy() {}
function session_register($name) {}
function session_start() {}
function session_cache_expire($new_cache_expire) {}
function session_name($name) {}
function session_module_name($module) {}
function session_decode($data) {}
function session_unset() {}
function session_id($id) {}
function session_save_path($path) {}
function session_set_cookie_params($lifetime, $path, $domain, $secure, $httponly) {}
function session_cache_limiter($cache_limiter) {}
function session_encode() {}
function session_unregister($name) {}
function session_set_save_handler($open, $close, $read, $write, $destroy, $gc) {}
function session_is_registered($name) {}
function session_write_close() {}
function session_regenerate_id($delete_old_session) {}
function ncurses_raw() {}
function ncurses_halfdelay($tenth) {}
function ncurses_reset_prog_mode() {}
function ncurses_mvinch($y, $x) {}
function ncurses_has_key($keycode) {}
function ncurses_flushinp() {}
function ncurses_panel_below($panel) {}
function ncurses_napms($milliseconds) {}
function ncurses_color_set($pair) {}
function ncurses_use_env($flag) {}
function ncurses_reset_shell_mode() {}
function ncurses_addchstr($s) {}
function ncurses_wstandend($window) {}
function ncurses_timeout($millisec) {}
function ncurses_mvwaddstr($window, $y, $x, $text) {}
function ncurses_move_panel($panel, $startx, $starty) {}
function ncurses_insdelln($count) {}
function ncurses_termname() {}
function ncurses_doupdate() {}
function ncurses_flash() {}
function ncurses_mouse_trafo($y, $x, $toscreen) {}
function ncurses_deleteln() {}
function ncurses_init_color($color, $r, $g, $b) {}
function ncurses_wcolor_set($window, $color_pair) {}
function ncurses_scr_init($filename) {}
function ncurses_top_panel($panel) {}
function ncurses_scr_restore($filename) {}
function ncurses_noecho() {}
function ncurses_mvaddch($y, $x, $c) {}
function ncurses_wnoutrefresh($window) {}
function ncurses_wattron($window, $attrs) {}
function ncurses_insch($character) {}
function ncurses_scr_dump($filename) {}
function ncurses_mvcur($old_y, $old_x, $new_y, $new_x) {}
function ncurses_newpad($rows, $cols) {}
function ncurses_addchnstr($s, $n) {}
function ncurses_has_il() {}
function ncurses_mvhline($y, $x, $attrchar, $n) {}
function ncurses_has_colors() {}
function ncurses_slk_attrset($intarg) {}
function ncurses_slk_color($intarg) {}
function ncurses_getch() {}
function ncurses_border($left, $right, $top, $bottom, $tl_corner, $tr_corner, $bl_corner, $br_corner) {}
function ncurses_init() {}
function ncurses_prefresh($pad, $pminrow, $pmincol, $sminrow, $smincol, $smaxrow, $smaxcol) {}
function ncurses_mousemask($newmask, $oldmask) {}
function ncurses_standout() {}
function ncurses_slk_touch() {}
function ncurses_wrefresh($window) {}
function ncurses_color_content($color, $r, $g, $b) {}
function ncurses_hline($charattr, $n) {}
function ncurses_vidattr($intarg) {}
function ncurses_standend() {}
function ncurses_slk_attroff($intarg) {}
function ncurses_curs_set($visibility) {}
function ncurses_mvaddstr($y, $x, $s) {}
function ncurses_wstandout($window) {}
function ncurses_mvaddchnstr($y, $x, $s, $n) {}
function ncurses_whline($window, $charattr, $n) {}
function ncurses_inch() {}
function ncurses_init_pair($pair, $fg, $bg) {}
function ncurses_getmouse($mevent) {}
function ncurses_nocbreak() {}
function ncurses_move($y, $x) {}
function ncurses_longname() {}
function ncurses_slk_noutrefresh() {}
function ncurses_ungetch($keycode) {}
function ncurses_end() {}
function ncurses_has_ic() {}
function ncurses_pnoutrefresh($pad, $pminrow, $pmincol, $sminrow, $smincol, $smaxrow, $smaxcol) {}
function ncurses_wattroff($window, $attrs) {}
function ncurses_hide_panel($panel) {}
function ncurses_attroff($attributes) {}
function ncurses_replace_panel($panel, $window) {}
function ncurses_pair_content($pair, $f, $b) {}
function ncurses_clrtobot() {}
function ncurses_slk_clear() {}
function ncurses_addch($ch) {}
function ncurses_insertln() {}
function ncurses_bottom_panel($panel) {}
function ncurses_slk_refresh() {}
function ncurses_delwin($window) {}
function ncurses_use_default_colors() {}
function ncurses_wmouse_trafo($window, $y, $x, $toscreen) {}
function ncurses_bkgd($attrchar) {}
function ncurses_keyok($keycode, $enable) {}
function ncurses_newwin($rows, $cols, $y, $x) {}
function ncurses_scr_set($filename) {}
function ncurses_nonl() {}
function ncurses_mvdelch($y, $x) {}
function ncurses_savetty() {}
function ncurses_cbreak() {}
function ncurses_can_change_color() {}
function ncurses_putp($text) {}
function ncurses_panel_above($panel) {}
function ncurses_refresh($ch) {}
function ncurses_termattrs() {}
function ncurses_attron($attributes) {}
function ncurses_attrset($attributes) {}
function ncurses_werase($window) {}
function ncurses_mvaddchstr($y, $x, $s) {}
function ncurses_clrtoeol() {}
function ncurses_define_key($definition, $keycode) {}
function ncurses_delch() {}
function ncurses_wborder($window, $left, $right, $top, $bottom, $tl_corner, $tr_corner, $bl_corner, $br_corner) {}
function ncurses_delay_output($milliseconds) {}
function ncurses_slk_restore() {}
function ncurses_getmaxyx($window, $y, $x) {}
function ncurses_slk_attr() {}
function ncurses_show_panel($panel) {}
function ncurses_start_color() {}
function ncurses_killchar() {}
function ncurses_def_prog_mode() {}
function ncurses_def_shell_mode() {}
function ncurses_echo() {}
function ncurses_instr($buffer) {}
function ncurses_keypad($window, $bf) {}
function ncurses_wattrset($window, $attrs) {}
function ncurses_echochar($character) {}
function ncurses_filter() {}
function ncurses_mvaddnstr($y, $x, $s, $n) {}
function ncurses_clear() {}
function ncurses_bkgdset($attrchar) {}
function ncurses_waddch($window, $ch) {}
function ncurses_meta($window, $_8bit) {}
function ncurses_mouseinterval($milliseconds) {}
function ncurses_wmove($window, $y, $x) {}
function ncurses_noqiflush() {}
function ncurses_slk_attron($intarg) {}
function ncurses_assume_default_colors($fg, $bg) {}
function ncurses_noraw() {}
function ncurses_ungetmouse($mevent) {}
function ncurses_getyx($window, $y, $x) {}
function ncurses_isendwin() {}
function ncurses_resetty() {}
function ncurses_vline($charattr, $n) {}
function ncurses_slk_init($format) {}
function ncurses_qiflush() {}
function ncurses_baudrate() {}
function ncurses_nl() {}
function ncurses_addnstr($s, $n) {}
function ncurses_new_panel($window) {}
function ncurses_panel_window($panel) {}
function ncurses_erasechar() {}
function ncurses_beep() {}
function ncurses_addstr($text) {}
function ncurses_wvline($window, $charattr, $n) {}
function ncurses_slk_set($labelnr, $label, $format) {}
function ncurses_update_panels() {}
function ncurses_waddstr($window, $str, $n) {}
function ncurses_mvgetch($y, $x) {}
function ncurses_wgetch($window) {}
function ncurses_erase() {}
function ncurses_wclear($window) {}
function ncurses_scrl($count) {}
function ncurses_use_extended_names($flag) {}
function ncurses_insstr($text) {}
function ncurses_typeahead($fd) {}
function ncurses_mvvline($y, $x, $attrchar, $n) {}
function ncurses_del_panel($panel) {}
function udm_close_stored($agent, $link) {}
function udm_clear_search_limits($agent) {}
function udm_set_agent_param($agent, $var, $val) {}
function udm_cat_list($agent, $category) {}
function udm_free_res($res) {}
function udm_hash32($agent, $str) {}
function udm_open_stored($agent, $storedaddr) {}
function udm_get_res_param($res, $param) {}
function udm_add_search_limit($agent, $var, $val) {}
function udm_error($agent) {}
function udm_check_stored($agent, $link, $doc_id) {}
function udm_api_version() {}
function udm_alloc_agent($dbaddr, $dbmode) {}
function udm_cat_path($agent, $category) {}
function udm_free_ispell_data($agent) {}
function udm_check_charset($agent, $charset) {}
function udm_alloc_agent_array($databases) {}
function udm_find($agent, $query) {}
function udm_load_ispell_data($agent, $var, $val1, $val2, $flag) {}
function udm_free_agent($agent) {}
function udm_errno($agent) {}
function udm_get_doc_count($agent) {}
function udm_crc32($agent, $str) {}
function udm_get_res_field($res, $row, $field) {}
function iis_stop_service($service_id) {}
function iis_stop_server($server_instance) {}
function iis_get_script_map($server_instance, $virtual_path, $script_extension) {}
function iis_get_server_rights($server_instance, $virtual_path) {}
function iis_set_script_map($server_instance, $virtual_path, $script_extension, $engine_path, $allow_scripting) {}
function iis_get_service_state($service_id) {}
function iis_get_server_by_comment($comment) {}
function iis_set_app_settings($server_instance, $virtual_path, $application_scope) {}
function iis_remove_server($server_instance) {}
function iis_add_server($path, $comment, $server_ip, $port, $host_name, $rights, $start_server) {}
function iis_set_server_rights($server_instance, $virtual_path, $directory_flags) {}
function iis_set_dir_security($server_instance, $virtual_path, $directory_flags) {}
function iis_get_dir_security($server_instance, $virtual_path) {}
function iis_get_server_by_path($path) {}
function iis_start_server($server_instance) {}
function iis_start_service($service_id) {}
function mb_stristr($haystack, $needle, $part, $encoding) {}
function mb_output_handler($contents, $status) {}
function mb_stripos($haystack, $needle, $offset, $encoding) {}
function mb_http_output($encoding) {}
function mb_preferred_mime_name($encoding) {}
function mb_ereg_search_regs($pattern, $option) {}
function mb_strimwidth($str, $start, $width, $trimmarker, $encoding) {}
function mb_strcut($str, $start, $length, $encoding) {}
function mb_encode_mimeheader($str, $charset, $transfer_encoding, $linefeed, $indent) {}
function mb_strrchr($haystack, $needle, $part, $encoding) {}
function mb_language($language) {}
function mb_ereg_search_init($string, $pattern, $option) {}
function mb_split($pattern, $string, $limit) {}
function mb_convert_encoding($str, $to_encoding, $from_encoding) {}
function mb_strlen($str, $encoding) {}
function mb_strtolower($str, $encoding) {}
function mb_decode_mimeheader($str) {}
function mb_detect_order($encoding_list) {}
function mb_regex_encoding($encoding) {}
function mb_substitute_character($substrchar) {}
function mb_ereg($pattern, $string, $regs) {}
function mb_ereg_match($pattern, $string, $option) {}
function mb_http_input($type) {}
function mb_ereg_search($pattern, $option) {}
function mb_list_encodings() {}
function mb_strpos($haystack, $needle, $offset, $encoding) {}
function mb_decode_numericentity($str, $convmap, $encoding) {}
function mb_detect_encoding($str, $encoding_list, $strict) {}
function mb_get_info($type) {}
function mb_parse_str($encoded_string, $result) {}
function mb_internal_encoding($encoding) {}
function mb_ereg_search_pos($pattern, $option) {}
function mb_convert_variables($to_encoding, $from_encoding, $vars) {}
function mb_strrpos($haystack, $needle, $offset, $encoding) {}
function mb_strripos($haystack, $needle, $offset, $encoding) {}
function mb_ereg_search_getregs() {}
function mb_eregi_replace($pattern, $replace, $string, $option) {}
function mb_ereg_search_setpos($position) {}
function mb_strstr($haystack, $needle, $part, $encoding) {}
function mb_send_mail($to, $subject, $message, $additional_headers, $additional_parameter) {}
function mb_eregi($pattern, $string, $regs) {}
function mb_convert_kana($str, $option, $encoding) {}
function mb_strtoupper($str, $encoding) {}
function mb_substr($str, $start, $length, $encoding) {}
function mb_regex_set_options($options) {}
function mb_ereg_search_getpos() {}
function mb_strwidth($str, $encoding) {}
function mb_check_encoding($var, $encoding) {}
function mb_convert_case($str, $mode, $encoding) {}
function mb_ereg_replace($pattern, $replacement, $string, $option) {}
function mb_strrichr($haystack, $needle, $part, $encoding) {}
function mb_substr_count($haystack, $needle, $encoding) {}
function mb_encode_numericentity($str, $convmap, $encoding) {}
function mcrypt_list_algorithms($lib_dir) {}
function mcrypt_module_self_test($algorithm, $lib_dir) {}
function mcrypt_enc_get_key_size($td) {}
function mcrypt_generic_init($td, $key, $iv) {}
function mcrypt_enc_is_block_algorithm($td) {}
function mcrypt_get_key_size($cipher) {}
function mcrypt_enc_self_test($td) {}
function mcrypt_module_get_algo_key_size($algorithm, $lib_dir) {}
function mcrypt_enc_get_modes_name($td) {}
function mcrypt_enc_is_block_algorithm_mode($td) {}
function mcrypt_enc_get_algorithms_name($td) {}
function mcrypt_cfb($cipher, $key, $data, $mode, $iv) {}
function mcrypt_module_get_supported_key_sizes($algorithm, $lib_dir) {}
function mcrypt_cbc($cipher, $key, $data, $mode, $iv) {}
function mcrypt_module_get_algo_block_size($algorithm, $lib_dir) {}
function mcrypt_decrypt($cipher, $key, $data, $mode, $iv) {}
function mcrypt_enc_get_supported_key_sizes($td) {}
function mcrypt_ofb($cipher, $key, $data, $mode, $iv) {}
function mcrypt_module_close($td) {}
function mcrypt_generic($td, $data) {}
function mcrypt_get_iv_size($cipher, $mode) {}
function mcrypt_enc_get_block_size($td) {}
function mcrypt_encrypt($cipher, $key, $data, $mode, $iv) {}
function mcrypt_get_block_size($cipher) {}
function mcrypt_create_iv($size, $source) {}
function mcrypt_module_is_block_algorithm_mode($mode, $lib_dir) {}
function mcrypt_module_is_block_mode($mode, $lib_dir) {}
function mcrypt_enc_is_block_mode($td) {}
function mcrypt_generic_deinit($td) {}
function mcrypt_module_open($algorithm, $algorithm_directory, $mode, $mode_directory) {}
function mdecrypt_generic($td, $data) {}
function mcrypt_enc_get_iv_size($td) {}
function mcrypt_list_modes($lib_dir) {}
function mcrypt_get_cipher_name($cipher) {}
function mcrypt_generic_end($td) {}
function mcrypt_ecb($cipher, $key, $data, $mode) {}
function mcrypt_module_is_block_algorithm($algorithm, $lib_dir) {}
function msession_find($name, $value) {}
function msession_listvar($name) {}
function msession_set_data($session, $value) {}
function msession_randstr($param) {}
function msession_set_array($session, $tuples) {}
function msession_destroy($name) {}
function msession_get($session, $name, $value) {}
function msession_disconnect() {}
function msession_inc($session, $name) {}
function msession_create($session, $classname, $data) {}
function msession_list() {}
function msession_get_array($session) {}
function msession_count() {}
function msession_plugin($session, $val, $param) {}
function msession_connect($host, $port) {}
function msession_set($session, $name, $value) {}
function msession_get_data($session) {}
function msession_lock($name) {}
function msession_timeout($session, $param) {}
function msession_unlock($session, $key) {}
function msession_uniq($param, $classname, $data) {}
function iterator_to_array($iterator, $use_keys) {}
function iterator_count($iterator) {}
function spl_autoload_call($class_name) {}
function spl_autoload_functions() {}
function spl_classes() {}
function spl_autoload_unregister($autoload_function) {}
function spl_object_hash($obj) {}
function spl_autoload($class_name, $file_extensions) {}
function spl_autoload_register($autoload_function) {}
function spl_autoload_extensions($file_extensions) {}
function class_implements($class, $autoload) {}
function class_parents($class, $autoload) {}
function tidy_getopt($object, $option) {}
function tidy_get_status($object) {}
function tidy_get_head($object) {}
function tidy_get_body($object) {}
function tidy_setopt($option, $value) {}
function tidy_parse_file($filename, $config, $encoding, $use_include_path) {}
function tidy_get_html($object) {}
function tidy_repair_file($filename, $config, $encoding, $use_include_path) {}
function tidy_get_root($object) {}
function ob_tidyhandler($input, $mode) {}
function tidy_error_count($object) {}
function tidy_config_count($object) {}
function tidy_is_xml($object) {}
function tidy_diagnose($object) {}
function tidy_save_config($filename) {}
function tidy_load_config($filename, $encoding) {}
function tidy_get_error_buffer($object) {}
function tidy_parse_string($input, $config, $encoding) {}
function tidy_reset_config() {}
function tidy_warning_count($object) {}
function tidy_get_output($object) {}
function tidy_get_config($object) {}
function tidy_get_opt_doc($object, $optname) {}
function tidy_is_xhtml($object) {}
function tidy_get_html_ver($object) {}
function tidy_access_count($object) {}
function tidy_repair_string($data, $config, $encoding) {}
function tidy_get_release() {}
function tidy_set_encoding($encoding) {}
function tidy_clean_repair($object) {}
function gopher_parsedir($dirent) {}
function zip_close($zip) {}
function zip_entry_name($zip_entry) {}
function zip_read($zip) {}
function zip_entry_open($zip, $zip_entry, $mode) {}
function zip_entry_filesize($zip_entry) {}
function zip_entry_compressedsize($zip_entry) {}
function zip_entry_compressionmethod($zip_entry) {}
function zip_entry_close($zip_entry) {}
function zip_entry_read($zip_entry, $length) {}
function zip_open($filename) {}
function apc_load_constants($key, $case_sensitive) {}
function apc_fetch($key) {}
function apc_define_constants($key, $constants, $case_sensitive) {}
function apc_store($key, $var, $ttl) {}
function apc_add($key, $var, $ttl) {}
function apc_delete($key) {}
function apc_sma_info($limited) {}
function apc_compile_file($filename) {}
function apc_cache_info($cache_type, $limited) {}
function apc_clear_cache($cache_type) {}
function socket_set_nonblock($socket) {}
function socket_recv($socket, $buf, $len, $flags) {}
function socket_create_listen($port, $backlog) {}
function socket_set_block($socket) {}
function socket_close($socket) {}
function socket_connect($socket, $address, $port) {}
function socket_strerror($errno) {}
function socket_getsockname($socket, $addr, $port) {}
function socket_shutdown($socket, $how) {}
function socket_listen($socket, $backlog) {}
function socket_send($socket, $buf, $len, $flags) {}
function socket_accept($socket) {}
function socket_recvfrom($socket, $buf, $len, $flags, $name, $port) {}
function socket_create_pair($domain, $type, $protocol, $fd) {}
function socket_get_option($socket, $level, $optname) {}
function socket_clear_error($socket) {}
function socket_write($socket, $buffer, $length) {}
function socket_read($socket, $length, $type) {}
function socket_getpeername($socket, $address, $port) {}
function socket_bind($socket, $address, $port) {}
function socket_create($domain, $type, $protocol) {}
function socket_last_error($socket) {}
function socket_sendto($socket, $buf, $len, $flags, $addr, $port) {}
function socket_select($read, $write, $except, $tv_sec, $tv_usec) {}
function socket_set_option($socket, $level, $optname, $optval) {}
function ftp_fput($ftp_stream, $remote_file, $handle, $mode, $startpos) {}
function ftp_pwd($ftp_stream) {}
function ftp_alloc($ftp_stream, $filesize, $result) {}
function ftp_delete($ftp_stream, $path) {}
function ftp_rename($ftp_stream, $oldname, $newname) {}
function ftp_get($ftp_stream, $local_file, $remote_file, $mode, $resumepos) {}
function ftp_chmod($ftp_stream, $mode, $filename) {}
function ftp_raw($ftp_stream, $command) {}
function ftp_fget($ftp_stream, $handle, $remote_file, $mode, $resumepos) {}
function ftp_nb_put($ftp_stream, $remote_file, $local_file, $mode, $startpos) {}
function ftp_systype($ftp_stream) {}
function ftp_rmdir($ftp_stream, $directory) {}
function ftp_put($ftp_stream, $remote_file, $local_file, $mode, $startpos) {}
function ftp_size($ftp_stream, $remote_file) {}
function ftp_connect($host, $port, $timeout) {}
function ftp_mkdir($ftp_stream, $directory) {}
function ftp_nb_get($ftp_stream, $local_file, $remote_file, $mode, $resumepos) {}
function ftp_close($ftp_stream) {}
function ftp_rawlist($ftp_stream, $directory, $recursive) {}
function ftp_nlist($ftp_stream, $directory) {}
function ftp_nb_fget($ftp_stream, $handle, $remote_file, $mode, $resumepos) {}
function ftp_exec($ftp_stream, $command) {}
function ftp_nb_continue($ftp_stream) {}
function ftp_pasv($ftp_stream, $pasv) {}
function ftp_login($ftp_stream, $username, $password) {}
function ftp_ssl_connect($host, $port, $timeout) {}
function ftp_mdtm($ftp_stream, $remote_file) {}
function ftp_get_option($ftp_stream, $option) {}
function ftp_chdir($ftp_stream, $directory) {}
function ftp_cdup($ftp_stream) {}
function ftp_site($ftp_stream, $command) {}
function ftp_set_option($ftp_stream, $option, $value) {}
function ftp_nb_fput($ftp_stream, $remote_file, $handle, $mode, $startpos) {}
function fribidi_log2vis($str, $direction, $charset) {}
function hw_api_object($parameter) {}
function hw_api_content($content, $mimetype) {}
function hwapi_hgcsp($hostname, $port) {}
function hw_api_attribute($name, $value) {}
function win32_ps_stat_proc($pid) {}
function win32_ps_stat_mem() {}
function win32_ps_list_procs() {}
function ctype_alnum($text) {}
function ctype_cntrl($text) {}
function ctype_graph($text) {}
function ctype_upper($text) {}
function ctype_digit($text) {}
function ctype_space($text) {}
function ctype_xdigit($text) {}
function ctype_punct($text) {}
function ctype_alpha($text) {}
function ctype_lower($text) {}
function ctype_print($text) {}
function timezone_open($timezone) {}
function date_timezone_set($object, $timezone) {}
function date_sunset($timestamp, $format, $latitude, $longitude, $zenith, $gmt_offset) {}
function date_timezone_get($object) {}
function timezone_offset_get($object, $datetime) {}
function timezone_abbreviations_list() {}
function strftime($format, $timestamp) {}
function date_create($time, $timezone) {}
function gmdate($format, $timestamp) {}
function date_default_timezone_get() {}
function time() {}
function strptime($date, $format) {}
function getdate($timestamp) {}
function date_offset_get($object) {}
function gmmktime($hour, $minute, $second, $month, $day, $year, $is_dst) {}
function mktime($hour, $minute, $second, $month, $day, $year, $is_dst) {}
function localtime($timestamp, $is_associative) {}
function date($format, $timestamp) {}
function date_format($object, $format) {}
function microtime($get_as_float) {}
function date_sunrise($timestamp, $format, $latitude, $longitude, $zenith, $gmt_offset) {}
function strtotime($time, $now) {}
function idate($format, $timestamp) {}
function date_modify($object, $modify) {}
function date_sub($object, $interval) {}
function date_date_set($object, $year, $month, $day) {}
function timezone_name_from_abbr($abbr, $gmtOffset, $isdst) {}
function date_add($object, $interval) {}
function timezone_identifiers_list() {}
function date_default_timezone_set($timezone_identifier) {}
function checkdate($month, $day, $year) {}
function date_isodate_set($object, $year, $week, $day) {}
function date_parse($date) {}
function gettimeofday($return_float) {}
function timezone_transitions_get($object) {}
function gmstrftime($format, $timestamp) {}
function date_sun_info($time, $latitude, $longitude) {}
function timezone_name_get($object) {}
function date_time_set($object, $hour, $minute, $second) {}
function finfo_set_flags($finfo, $options) {}
function finfo_close($finfo) {}
function finfo_file($finfo, $file_name, $options, $context) {}
function finfo_buffer($finfo, $string, $options, $context) {}
function finfo_open($options, $arg) {}
function sybase_result($result, $row, $field) {}
function sybase_fetch_array($result) {}
function sybase_unbuffered_query($query, $link_identifier, $store_result) {}
function sybase_query($query, $link_identifier) {}
function sybase_min_message_severity($severity) {}
function sybase_affected_rows($link_identifier) {}
function sybase_connect($servername, $username, $password, $charset, $appname) {}
function sybase_fetch_row($result) {}
function sybase_min_server_severity($severity) {}
function sybase_min_error_severity($severity) {}
function sybase_pconnect($servername, $username, $password, $charset, $appname) {}
function sybase_data_seek($result_identifier, $row_number) {}
function sybase_free_result($result) {}
function sybase_field_seek($result, $field_offset) {}
function sybase_deadlock_retry_count($retry_count) {}
function sybase_close($link_identifier) {}
function sybase_min_client_severity($severity) {}
function sybase_fetch_field($result, $field_offset) {}
function sybase_fetch_assoc($result) {}
function sybase_num_rows($result) {}
function sybase_set_message_handler($handler, $connection) {}
function sybase_select_db($database_name, $link_identifier) {}
function sybase_get_last_message() {}
function sybase_fetch_object($result, $object) {}
function sybase_num_fields($result) {}
function shmop_write($shmid, $data, $offset) {}
function shmop_read($shmid, $start, $count) {}
function shmop_delete($shmid) {}
function shmop_open($key, $flags, $mode, $size) {}
function shmop_size($shmid) {}
function shmop_close($shmid) {}
function inclued_get_data() {}
function db2_columns($connection, $qualifier, $schema, $tablename, $columnname) {}
function db2_fetch_array($stmt, $row_number) {}
function db2_result($stmt, $column) {}
function db2_set_option($resource, $options, $type) {}
function db2_close($connection) {}
function db2_field_type($stmt, $column) {}
function db2_primary_keys($connection, $qualifier, $schema, $tablename) {}
function db2_num_rows($stmt) {}
function db2_field_width($stmt, $column) {}
function db2_free_result($stmt) {}
function db2_field_precision($stmt, $column) {}
function db2_execute($stmt, $parameters) {}
function db2_get_option($resource, $option) {}
function db2_free_stmt($stmt) {}
function db2_conn_error($connection) {}
function db2_server_info($connection) {}
function db2_special_columns($connection, $qualifier, $schema, $table_name, $scope) {}
function db2_lob_read($stmt, $colnum, $length) {}
function db2_stmt_error($stmt) {}
function db2_stmt_errormsg($stmt) {}
function db2_commit($connection) {}
function db2_field_num($stmt, $column) {}
function db2_next_result($stmt) {}
function db2_autocommit($connection, $value) {}
function db2_client_info($connection) {}
function db2_fetch_row($stmt, $row_number) {}
function db2_cursor_type($stmt) {}
function db2_field_scale($stmt, $column) {}
function db2_fetch_object($stmt, $row_number) {}
function db2_connect($database, $username, $password, $options) {}
function db2_procedures($connection, $qualifier, $schema, $procedure) {}
function db2_field_name($stmt, $column) {}
function db2_field_display_size($stmt, $column) {}
function db2_fetch_both($stmt, $row_number) {}
function db2_pconnect($database, $username, $password, $options) {}
function db2_rollback($connection) {}
function db2_escape_string($string_literal) {}
function db2_prepare($connection, $statement, $options) {}
function db2_bind_param($stmt, $parameternumber, $variablename, $parametertype, $datatype, $precision, $scale) {}
function db2_procedure_columns($connection, $qualifier, $schema, $procedure, $parameter) {}
function db2_foreign_keys($connection, $qualifier, $schema, $tablename) {}
function db2_tables($connection, $qualifier, $schema, $tablename, $tabletype) {}
function db2_column_privileges($connection, $qualifier, $schema, $tablename, $columnname) {}
function db2_fetch_assoc($stmt, $row_number) {}
function db2_conn_errormsg($connection) {}
function db2_table_privileges($connection, $qualifier, $schema, $table_name) {}
function db2_exec($connection, $statement, $options) {}
function db2_statistics($connection, $qualifier, $schema, $tablename, $unique) {}
function db2_num_fields($stmt) {}
function xml_set_start_namespace_decl_handler($parser, $handler) {}
function xml_error_string($code) {}
function xml_parser_create_ns($encoding, $separator) {}
function xml_get_current_byte_index($parser) {}
function xml_parse($parser, $data, $is_final) {}
function xml_parse_into_struct($parser, $data, $values, $index) {}
function utf8_decode($data) {}
function utf8_encode($data) {}
function xml_get_error_code($parser) {}
function xml_set_processing_instruction_handler($parser, $handler) {}
function xml_parser_set_option($parser, $option, $value) {}
function xml_set_character_data_handler($parser, $handler) {}
function xml_set_external_entity_ref_handler($parser, $handler) {}
function xml_set_default_handler($parser, $handler) {}
function xml_get_current_line_number($parser) {}
function xml_parser_get_option($parser, $option) {}
function xml_parser_create($encoding) {}
function xml_set_unparsed_entity_decl_handler($parser, $handler) {}
function xml_set_notation_decl_handler($parser, $handler) {}
function xml_set_element_handler($parser, $start_element_handler, $end_element_handler) {}
function xml_get_current_column_number($parser) {}
function xml_set_end_namespace_decl_handler($parser, $handler) {}
function xml_set_object($parser, $object) {}
function xml_parser_free($parser) {}
function vpopmail_set_user_quota($user, $domain, $quota) {}
function vpopmail_add_domain_ex($domain, $passwd, $quota, $bounce, $apop) {}
function vpopmail_add_user($user, $domain, $password, $gecos, $apop) {}
function vpopmail_alias_del_domain($domain) {}
function vpopmail_error() {}
function vpopmail_add_alias_domain_ex($olddomain, $newdomain) {}
function vpopmail_add_domain($domain, $dir, $uid, $gid) {}
function vpopmail_del_domain($domain) {}
function vpopmail_alias_get($alias, $domain) {}
function vpopmail_alias_del($user, $domain) {}
function vpopmail_alias_get_all($domain) {}
function vpopmail_alias_add($user, $domain, $alias) {}
function vpopmail_auth_user($user, $domain, $password, $apop) {}
function vpopmail_del_user($user, $domain) {}
function vpopmail_add_alias_domain($domain, $aliasdomain) {}
function vpopmail_passwd($user, $domain, $password, $apop) {}
function vpopmail_del_domain_ex($domain) {}
function dio_truncate($fd, $offset) {}
function dio_write($fd, $data, $len) {}
function dio_read($fd, $len) {}
function dio_open($filename, $flags, $mode) {}
function dio_close($fd) {}
function dio_seek($fd, $pos, $whence) {}
function dio_tcsetattr($fd, $options) {}
function dio_stat($fd) {}
function dio_fcntl($fd, $cmd, $args) {}
function opendir($path, $context) {}
function getcwd() {}
function closedir($dir_handle) {}
function chroot($directory) {}
function chdir($directory) {}
function scandir($directory, $sorting_order, $context) {}
function rewinddir($dir_handle) {}
function readdir($dir_handle) {}
function token_get_all($source) {}
function token_name($token) {}
function w32api_register_function($library, $function_name, $return_type) {}
function w32api_init_dtype($typename, $value) {}
function w32api_invoke_function($funcname, $argument) {}
function w32api_set_call_method($method) {}
function w32api_deftype($typename, $member1_type, $member1_name) {}
function xattr_list($filename, $flags) {}
function xattr_get($filename, $name, $flags) {}
function xattr_set($filename, $name, $value, $flags) {}
function xattr_remove($filename, $name, $flags) {}
function xattr_supported($filename, $flags) {}
function use_soap_error_handler($handler) {}
function is_soap_fault($obj) {}
function curl_setopt_array($ch, $options) {}
function curl_init($url) {}
function curl_multi_close($mh) {}
function curl_multi_getcontent($ch) {}
function curl_exec($ch) {}
function curl_multi_select($mh, $timeout) {}
function curl_multi_exec($mh, $still_running) {}
function curl_multi_remove_handle($mh, $ch) {}
function curl_getinfo($ch, $opt) {}
function curl_multi_init() {}
function curl_multi_info_read($mh, $msgs_in_queue) {}
function curl_error($ch) {}
function curl_copy_handle($ch) {}
function curl_setopt($ch, $option, $value) {}
function curl_multi_add_handle($mh, $ch) {}
function curl_errno($ch) {}
function curl_close($ch) {}
function curl_version($age) {}
function ereg($pattern, $string, $regs) {}
function ereg_replace($pattern, $replacement, $string) {}
function eregi($pattern, $string, $regs) {}
function eregi_replace($pattern, $replacement, $string) {}
function split($pattern, $string, $limit) {}
function spliti($pattern, $string, $limit) {}
function sql_regcase($string) {}
function flush() {}
function output_add_rewrite_var($name, $value) {}
function ob_flush() {}
function ob_list_handlers() {}
function ob_get_flush() {}
function ob_implicit_flush($flag) {}
function ob_get_level() {}
function ob_start($output_callback, $chunk_size, $erase) {}
function ob_gzhandler($buffer, $mode) {}
function ob_get_length() {}
function ob_get_contents() {}
function output_reset_rewrite_vars() {}
function ob_end_flush() {}
function ob_get_status($full_status) {}
function ob_end_clean() {}
function ob_get_clean() {}
function ob_clean() {}
function mailparse_msg_parse($mimemail, $data) {}
function mailparse_msg_extract_part($mimemail, $msgbody, $callbackfunc) {}
function mailparse_uudecode_all($fp) {}
function mailparse_msg_parse_file($filename) {}
function mailparse_msg_get_part($mimemail, $mimesection) {}
function mailparse_msg_extract_part_file($mimemail, $filename, $callbackfunc) {}
function mailparse_msg_create() {}
function mailparse_rfc822_parse_addresses($addresses) {}
function mailparse_determine_best_xfer_encoding($fp) {}
function mailparse_msg_free($mimemail) {}
function mailparse_msg_get_structure($mimemail) {}
function mailparse_stream_encode($sourcefp, $destfp, $encoding) {}
function mailparse_msg_extract_whole_part_file($mimemail, $filename, $callbackfunc) {}
function mailparse_msg_get_part_data($mimemail) {}
function maxdb_fetch_object($result) {}
function maxdb_ping($link) {}
function maxdb_query($link, $query, $resultmode) {}
function maxdb_real_escape_string($link, $escapestr) {}
function maxdb_character_set_name($link) {}
function maxdb_stmt_affected_rows($stmt) {}
function maxdb_get_server_info($link) {}
function maxdb_stmt_close_long_data($stmt, $param_nr) {}
function maxdb_error($link) {}
function maxdb_use_result($link) {}
function maxdb_get_client_info() {}
function maxdb_rpl_probe($link) {}
function maxdb_get_server_version($link) {}
function maxdb_rpl_parse_enabled($link) {}
function maxdb_stmt_store_result($stmt) {}
function maxdb_fetch_field($result) {}
function maxdb_stmt_num_rows($stmt) {}
function maxdb_fetch_row($result) {}
function maxdb_fetch_fields($result) {}
function maxdb_rpl_query_type($link) {}
function maxdb_stmt_fetch($stmt) {}
function maxdb_enable_reads_from_master($link) {}
function maxdb_affected_rows($link) {}
function maxdb_num_rows($result) {}
function maxdb_server_end() {}
function maxdb_close($link) {}
function maxdb_store_result($link) {}
function maxdb_report($flags) {}
function maxdb_commit($link) {}
function maxdb_fetch_field_direct($result, $fieldnr) {}
function maxdb_change_user($link, $user, $password, $database) {}
function maxdb_stmt_bind_param($stmt, $types, $var1) {}
function maxdb_errno($link) {}
function maxdb_field_count($link) {}
function maxdb_autocommit($link, $mode) {}
function maxdb_real_connect($link, $hostname, $username, $passwd, $dbname, $port, $socket) {}
function maxdb_fetch_assoc($result) {}
function maxdb_fetch_array($result, $resulttype) {}
function maxdb_free_result($result) {}
function maxdb_disable_reads_from_master($link) {}
function maxdb_field_tell($result) {}
function maxdb_get_host_info($link) {}
function maxdb_server_init($server, $groups) {}
function maxdb_stmt_close($stmt) {}
function maxdb_stmt_error($stmt) {}
function maxdb_sqlstate($link) {}
function maxdb_field_seek($result, $fieldnr) {}
function maxdb_info($link) {}
function maxdb_next_result($link) {}
function maxdb_warning_count($link) {}
function maxdb_stmt_sqlstate($stmt) {}
function maxdb_stmt_data_seek($statement, $offset) {}
function maxdb_select_db($link, $dbname) {}
function maxdb_stmt_bind_result($stmt, $var1) {}
function maxdb_stmt_reset($stmt) {}
function maxdb_stmt_errno($stmt) {}
function maxdb_stmt_param_count($stmt) {}
function maxdb_stmt_result_metadata($stmt) {}
function maxdb_send_query($link, $query) {}
function maxdb_init() {}
function maxdb_get_client_version() {}
function maxdb_stmt_free_result($stmt) {}
function maxdb_fetch_lengths($result) {}
function maxdb_kill($link, $processid) {}
function maxdb_stat($link) {}
function maxdb_enable_rpl_parse($link) {}
function maxdb_thread_safe() {}
function maxdb_dump_debug_info($link) {}
function maxdb_real_query($link, $query) {}
function maxdb_stmt_execute($stmt) {}
function maxdb_more_results($link) {}
function maxdb_ssl_set($link, $key, $cert, $ca, $capath, $cipher) {}
function maxdb_connect_error() {}
function maxdb_data_seek($result, $offset) {}
function maxdb_stmt_send_long_data($stmt, $param_nr, $data) {}
function maxdb_multi_query($link, $query) {}
function maxdb_debug($debug) {}
function maxdb_stmt_init($link) {}
function maxdb_connect_errno() {}
function maxdb_connect($host, $username, $passwd, $dbname, $port, $socket) {}
function maxdb_insert_id($link) {}
function maxdb_get_proto_info($link) {}
function maxdb_embedded_connect($dbname) {}
function maxdb_stmt_prepare($stmt, $query) {}
function maxdb_thread_id($link) {}
function maxdb_rollback($link) {}
function maxdb_prepare($link, $query) {}
function maxdb_options($link, $option, $value) {}
function maxdb_disable_rpl_parse($link) {}
function maxdb_master_query($link, $query) {}
function maxdb_num_fields($result) {}
function radius_config($radius_handle, $file) {}
function radius_close($radius_handle) {}
function radius_strerror($radius_handle) {}
function radius_put_vendor_int($radius_handle, $vendor, $type, $value) {}
function radius_put_vendor_string($radius_handle, $vendor, $type, $value) {}
function radius_acct_open() {}
function radius_cvt_int($data) {}
function radius_auth_open() {}
function radius_put_vendor_addr($radius_handle, $vendor, $type, $addr) {}
function radius_demangle_mppe_key($radius_handle, $mangled) {}
function radius_server_secret($radius_handle) {}
function radius_get_vendor_attr($data) {}
function radius_send_request($radius_handle) {}
function radius_put_attr($radius_handle, $type, $value) {}
function radius_put_addr($radius_handle, $type, $addr) {}
function radius_get_attr($radius_handle) {}
function radius_put_string($radius_handle, $type, $value) {}
function radius_cvt_string($data) {}
function radius_create_request($radius_handle, $type) {}
function radius_add_server($radius_handle, $hostname, $port, $secret, $timeout, $max_tries) {}
function radius_request_authenticator($radius_handle) {}
function radius_demangle($radius_handle, $mangled) {}
function radius_put_vendor_attr($radius_handle, $vendor, $type, $value) {}
function radius_put_int($radius_handle, $type, $value) {}
function radius_cvt_addr($data) {}
function dotnet_load($assembly_name, $datatype_name, $codepage) {}
function aggregate($object, $class_name) {}
function aggregate_properties_by_regexp($object, $class_name, $regexp, $exclude) {}
function deaggregate($object, $class_name) {}
function aggregate_methods_by_regexp($object, $class_name, $regexp, $exclude) {}
function aggregate_properties_by_list($object, $class_name, $properties_list, $exclude) {}
function aggregate_info($object) {}
function aggregate_methods($object, $class_name) {}
function aggregate_methods_by_list($object, $class_name, $methods_list, $exclude) {}
function aggregate_properties($object, $class_name) {}
function get_class($object) {}
function call_user_method($method_name, $obj, $parameter) {}
function get_object_vars($object) {}
function get_parent_class($object) {}
function class_exists($class_name, $autoload) {}
function get_declared_classes() {}
function interface_exists($interface_name, $autoload) {}
function method_exists($object, $method_name) {}
function is_subclass_of($object, $class_name) {}
function property_exists($class, $property) {}
function get_class_methods($class_name) {}
function call_user_method_array($method_name, $obj, $params) {}
function get_declared_interfaces() {}
function get_class_vars($class_name) {}
function is_a($object, $class_name) {}
function tcpwrap_check($daemon, $address, $user, $nodns) {}
function unicode_set_error_mode($direction, $mode) {}
function unicode_set_subst_char($character) {}
function unicode_decode($input, $encoding, $errmode) {}
function unicode_get_subst_char() {}
function unicode_encode($input, $encoding, $errmode) {}
function unicode_get_error_mode($direction) {}
function mqseries_conn($qManagerName, $hconn, $compCode, $reason) {}
function mqseries_open($hconn, $objDesc, $option, $hobj, $compCode, $reason) {}
function mqseries_cmit($hconn, $compCode, $reason) {}
function mqseries_back($hconn, $compCode, $reason) {}
function mqseries_inq($hconn, $hobj, $selectorCount, $selectors, $intAttrCount, $intAttr, $charAttrLength, $charAttr, $compCode, $reason) {}
function mqseries_put1($hconn, $objDesc, $msgDesc, $pmo, $buffer, $compCode, $reason) {}
function mqseries_set($hconn, $compCode, $reason) {}
function mqseries_strerror($reason) {}
function mqseries_close($hconn, $hobj, $compCode, $reason) {}
function mqseries_get($hConn, $hObj, $md, $gmo, $bufferLength, $msg, $data_length, $compCode, $reason) {}
function mqseries_put($hConn, $hObj, $md, $pmo, $message, $compCode, $reason) {}
function mqseries_begin($hconn, $beginOptions, $compCode, $reason) {}
function mqseries_disc($hconn, $compCode, $reason) {}
function mqseries_connx($qManagerName, $connOptions, $hconn, $compCode, $reason) {}
function hash_copy($context) {}
function hash_update_file($context, $filename, $context) {}
function hash_file($algo, $filename, $raw_output) {}
function hash_hmac_file($algo, $filename, $key, $raw_output) {}
function hash_update_stream($context, $handle, $length) {}
function hash_update($context, $data) {}
function hash($algo, $data, $raw_output) {}
function hash_hmac($algo, $data, $key, $raw_output) {}
function hash_init($algo, $options, $key) {}
function hash_final($context, $raw_output) {}
function hash_algos() {}
function grapheme_stristr($haystack, $needle, $before_needle) {}
function intl_is_failure($error_code) {}
function intl_get_error_message() {}
function intl_error_name($error_code) {}
function grapheme_strpos($haystack, $needle, $offset) {}
function grapheme_strrpos($haystack, $needle, $offset) {}
function grapheme_strlen($input) {}
function intl_get_error_code() {}
function grapheme_strripos($haystack, $needle, $offset) {}
function grapheme_stripos($haystack, $needle, $offset) {}
function grapheme_substr($string, $start, $length) {}
function grapheme_strstr($haystack, $needle, $before_needle) {}
function grapheme_extract($haystack, $size, $extract_type, $start, $next) {}
function get_included_files() {}
function getmyinode() {}
function zend_logo_guid() {}
function phpversion($extension) {}
function get_magic_quotes_runtime() {}
function zend_version() {}
function zend_thread_id() {}
function get_loaded_extensions($zend_extensions) {}
function assert($assertion) {}
function php_ini_scanned_files() {}
function ini_get_all($extension, $details) {}
function getrusage($who) {}
function get_magic_quotes_gpc() {}
function memory_get_peak_usage($real_usage) {}
function memory_get_usage($real_usage) {}
function getenv($varname) {}
function getlastmod() {}
function php_sapi_name() {}
function sys_get_temp_dir() {}
function restore_include_path() {}
function get_cfg_var($option) {}
function phpcredits($flag) {}
function set_magic_quotes_runtime($new_setting) {}
function ini_set($varname, $newvalue) {}
function set_time_limit($seconds) {}
function get_include_path() {}
function extension_loaded($name) {}
function ini_restore($varname) {}
function version_compare($version1, $version2, $operator) {}
function getopt($options, $longopts) {}
function get_defined_constants($categorize) {}
function assert_options($what, $value) {}
function getmypid() {}
function getmyuid() {}
function php_logo_guid() {}
function dl($library) {}
function phpinfo($what) {}
function ini_get($varname) {}
function php_ini_loaded_file() {}
function get_current_user() {}
function php_uname($mode) {}
function set_include_path($new_include_path) {}
function get_extension_funcs($module_name) {}
function putenv($setting) {}
function getmygid() {}
class XMLReader {
    function moveToElement() {}
    function getAttributeNo($index) {}
    function next($localname) {}
    function moveToAttribute($name) {}
    function moveToAttributeNs($localName, $namespaceURI) {}
    function expand() {}
    function setParserProperty($property, $value) {}
    function getParserProperty($property) {}
    function open($URI, $encoding, $options) {}
    function read() {}
    function getAttributeNs($localName, $namespaceURI) {}
    function setRelaxNGSchemaSource($source) {}
    function getAttribute($name) {}
    function isValid() {}
    function moveToNextAttribute() {}
    function setRelaxNGSchema($filename) {}
    function lookupNamespace($prefix) {}
    function xml($source, $encoding, $options) {}
    function moveToAttributeNo($index) {}
    function moveToFirstAttribute() {}
    function close() {}
}
class PDO {
    function pgsqlLOBCreate() {}
    function pgsqlLOBOpen($oid, $mode) {}
    function pgsqlLOBUnlink($oid) {}
    function rollBack() {}
    function lastInsertId($name) {}
    function errorCode() {}
    function quote($string, $parameter_type) {}
    function exec($statement) {}
    function query($statement) {}
    function prepare($statement, $driver_options) {}
    function errorInfo() {}
    function getAttribute($attribute) {}
    function getAvailableDrivers() {}
    function setAttribute($attribute, $value) {}
    function beginTransaction() {}
    function commit() {}
}
class Memcache {
    function decrement($key, $value) {}
    function getVersion() {}
    function replace($key, $var, $flag, $expire) {}
    function delete($key, $timeout) {}
    function getExtendedStats($type, $slabid, $limit) {}
    function getStats($type, $slabid, $limit) {}
    function get($key, $flags) {}
    function flush() {}
    function setCompressThreshold($threshold, $min_savings) {}
    function getServerStatus($host, $port) {}
    function close() {}
    function increment($key, $value) {}
    function set($key, $var, $flag, $expire) {}
    function add($key, $var, $flag, $expire) {}
    function addServer($host, $port, $persistent, $weight, $timeout, $retry_interval, $status, $failure_callback) {}
    function connect($host, $port, $timeout) {}
    function pconnect($host, $port, $timeout) {}
    function setServerParams($host, $port, $timeout, $retry_interval, $status, $failure_callback) {}
}
class Phar {
    function compressAllFilesBZIP2() {}
    function offsetSet($offset, $value) {}
    function isWritable() {}
    function apiVersion() {}
    function createDefaultStub() {}
    function addFromString($localname, $contents) {}
    function decompress($extension) {}
    function compressAllFilesGZ() {}
    function offsetUnset($offset) {}
    function mapPhar($alias, $dataoffset) {}
    function uncompressAllFiles() {}
    function offsetGet($offset) {}
    function getMetaData() {}
    function getVersion() {}
    function running($retphar) {}
    function isBuffering() {}
    function unlinkArchive($archive) {}
    function buildFromIterator($iter, $base_directory) {}
    function getModified() {}
    function getStub() {}
    function getSupportedCompression() {}
    function compress($compression, $extension) {}
    function copy($oldfile, $newfile) {}
    function mount($pharpath, $externalpath) {}
    function webPhar($alias, $index, $f404, $mimetypes, $rewrites) {}
    function getSupportedSignatures() {}
    function addEmptyDir($dirname) {}
    function canWrite() {}
    function isFileFormat($format) {}
    function interceptFileFuncs() {}
    function isValidPharFilename($filename, $executable) {}
    function setSignatureAlgorithm($sigtype, $privatekey) {}
    function startBuffering() {}
    function stopBuffering() {}
    function mungServer($munglist) {}
    function setStub($stub) {}
    function convertToExecutable($format, $compression, $extension) {}
    function getSignature() {}
    function addFile($file, $localname) {}
    function convertToData($format, $compression, $extension) {}
    function buildFromDirectory($base_dir, $regex) {}
    function decompressFiles() {}
    function isCompressed() {}
    function delete($entry) {}
    function __construct($fname, $flags, $alias) {}
    function offsetExists($offset) {}
    function hasMetadata() {}
    function setMetadata($metadata) {}
    function extractTo($pathto, $files, $overwrite) {}
    function canCompress($type) {}
    function compressFiles($compression) {}
    function setAlias($alias) {}
    function setDefaultStub($index, $webindex) {}
    function delMetadata() {}
    function count() {}
    function loadPhar($filename, $alias) {}
}
class PharFileInfo {
    function decompress() {}
    function setUncompressed() {}
    function setCompressedGZ() {}
    function getMetaData() {}
    function compress($compression) {}
    function chmod($permissions) {}
    function setCompressedBZIP2() {}
    function isCRCChecked() {}
    function getCompressedSize() {}
    function isCompressedBZIP2() {}
    function isCompressed() {}
    function getPharFlags() {}
    function __construct($entry) {}
    function getCRC32() {}
    function hasMetadata() {}
    function setMetaData($metadata) {}
    function isCompressedGZ() {}
    function delMetadata() {}
}
class PharData {
    function offsetSet($offset, $value) {}
    function isWritable() {}
    function addFromString($localname, $contents) {}
    function decompress($extension) {}
    function offsetUnset($offset) {}
    function buildFromIterator($iter, $base_directory) {}
    function compress($compression, $extension) {}
    function copy($oldfile, $newfile) {}
    function addEmptyDir($dirname) {}
    function setStub($stub) {}
    function convertToExecutable($format, $compression, $extension) {}
    function convertToData($format, $compression, $extension) {}
    function decompressFiles() {}
    function delete($entry) {}
    function __construct($fname, $flags) {}
    function extractTo($pathto, $files, $overwrite) {}
    function compressFiles($compression) {}
    function setAlias($alias) {}
    function setDefaultStub($index, $webindex) {}
    function delMetadata() {}
}
class SphinxClient {
    function setRetries($count, $delay) {}
    function buildKeywords($query, $index, $hits) {}
    function setMaxQueryTime($qtime) {}
    function setIDRange($min, $max) {}
    function buildExcerpts($docs, $index, $words, $opts) {}
    function resetFilters() {}
    function addQuery($query, $index, $comment) {}
    function updateAttributes($index, $attributes, $values) {}
    function resetGroupBy() {}
    function setRankingMode($ranker) {}
    function setFilter($attribute, $values, $exclude) {}
    function setFieldWeights($weights) {}
    function query($query, $index, $comment) {}
    function setLimits($offset, $limit, $max, $cutoff) {}
    function setServer($server, $port) {}
    function setGroupDistinct($attribute) {}
    function getLastError() {}
    function setGeoAnchor($attrlat, $attrlong, $latitude, $longitude) {}
    function runQueries() {}
    function setMatchMode($mode) {}
    function setFilterFloatRange($attribute, $min, $max, $exclude) {}
    function getLastWarning() {}
    function setFilterRange($attribute, $min, $max, $exclude) {}
    function setSortMode($mode, $sortby) {}
    function __construct() {}
    function escapeString($string) {}
    function setConnectTimeout($timeout) {}
    function setGroupBy($attribute, $func, $groupsort) {}
    function setIndexWeights($weights) {}
    function setArrayResult($array_result) {}
}
class DomDocument {
    function create_cdata_section($content) {}
    function get_elements_by_tagname($name) {}
    function create_text_node($content) {}
    function doctype() {}
    function create_attribute($name, $value) {}
    function get_element_by_id($id) {}
    function dump_file($filename, $compressionmode, $format) {}
    function html_dump_mem() {}
    function create_entity_reference($content) {}
    function dump_mem($format, $encoding) {}
    function document_element() {}
    function xinclude() {}
    function create_element_ns($uri, $name, $prefix) {}
    function create_element($name) {}
    function create_comment($content) {}
    function add_root($name) {}
    function create_processing_instruction($content) {}
    function validate() {}
    function relaxNGValidateSource($source) {}
    function saveXML($node, $options) {}
    function createElementNS($namespaceURI, $qualifiedName, $value) {}
    function getElementsByTagNameNS($namespaceURI, $localName) {}
    function createElement($name, $value) {}
    function registerNodeClass($baseclass, $extendedclass) {}
    function load($filename, $options) {}
    function createDocumentFragment() {}
    function loadXML($source, $options) {}
    function relaxNGValidate($filename) {}
    function loadHTML($source) {}
    function createEntityReference($name) {}
    function getElementById($elementId) {}
    function saveHTMLFile($filename) {}
    function loadHTMLFile($filename) {}
    function createAttributeNS($namespaceURI, $qualifiedName) {}
    function createCDATASection($data) {}
    function schemaValidate($filename) {}
    function createTextNode($content) {}
    function schemaValidateSource($source) {}
    function createComment($data) {}
    function getElementsByTagName($name) {}
    function __construct($version, $encoding) {}
    function importNode($importedNode, $deep) {}
    function save($filename, $options) {}
    function normalizeDocument() {}
    function saveHTML() {}
    function createAttribute($name) {}
    function createProcessingInstruction($target, $data) {}
}
class DomNode {
    function has_attributes() {}
    function append_sibling($newnode) {}
    function clone_node() {}
    function parent_node() {}
    function insert_before($newnode, $refnode) {}
    function replace_node($newnode) {}
    function has_child_nodes() {}
    function first_child() {}
    function owner_document() {}
    function is_blank_node() {}
    function previous_sibling() {}
    function node_value() {}
    function set_namespace($uri, $prefix) {}
    function child_nodes() {}
    function unlink_node() {}
    function remove_child($oldchild) {}
    function prefix() {}
    function node_type() {}
    function attributes() {}
    function last_child() {}
    function set_content($content) {}
    function next_sibling() {}
    function get_content() {}
    function set_name() {}
    function node_name() {}
    function dump_node() {}
    function replace_child($newnode, $oldnode) {}
    function removeChild($oldnode) {}
    function insertBefore($newnode, $refnode) {}
    function lookupPrefix($namespaceURI) {}
    function hasAttributes() {}
    function normalize() {}
    function replaceChild($newnode, $oldnode) {}
    function isDefaultNamespace($namespaceURI) {}
    function cloneNode($deep) {}
    function lookupNamespaceURI($prefix) {}
    function isSupported($feature, $version) {}
    function hasChildNodes() {}
    function isSameNode($node) {}
    function appendChild($newnode) {}
}
class Runkit_Sandbox_Parent {
    function __construct() {}
}
class SCA {
    function getService($target, $binding, $config) {}
    function createDataObject($type_namespace_uri, $type_name) {}
}
class SCA_LocalProxy {
    function createDataObject($type_namespace_uri, $type_name) {}
}
class SCA_SoapProxy {
    function createDataObject($type_namespace_uri, $type_name) {}
}
class DomDocumentFragment {
    function appendXML($data) {}
}
class DomNodelist {
    function item($index) {}
}
class DomCharacterData {
    function replaceData($offset, $count, $data) {}
    function appendData($data) {}
    function insertData($offset, $data) {}
    function substringData($offset, $count) {}
    function deleteData($offset, $count) {}
}
class DomText {
    function splitText($offset) {}
    function isWhitespaceInElementContent() {}
}
class DomImplementation {
    function createDocument($namespaceURI, $qualifiedName, $doctype) {}
    function createDocumentType($qualifiedName, $publicId, $systemId) {}
    function hasFeature($feature, $version) {}
}
class DomAttr {
    function isId() {}
    function __construct($name, $value) {}
}
class DomElement {
    function hasAttribute($name) {}
    function setAttributeNS($namespaceURI, $qualifiedName, $value) {}
    function setIdAttributeNode($attr, $isId) {}
    function getElementsByTagNameNS($namespaceURI, $localName) {}
    function removeAttributeNS($namespaceURI, $localName) {}
    function setAttributeNodeNS($attr) {}
    function setAttributeNode($attr) {}
    function getAttributeNS($namespaceURI, $localName) {}
    function setIdAttributeNS($namespaceURI, $localName, $isId) {}
    function setIdAttribute($name, $isId) {}
    function hasAttributeNS($namespaceURI, $localName) {}
    function getAttribute($name) {}
    function getElementsByTagName($name) {}
    function removeAttributeNode($oldnode) {}
    function setAttribute($name, $value) {}
    function getAttributeNode($name) {}
    function removeAttribute($name) {}
    function getAttributeNodeNS($namespaceURI, $localName) {}
}
class DomXPath {
    function query($expression, $contextnode) {}
    function registerNamespace($prefix, $namespaceURI) {}
    function evaluate($expression, $contextnode) {}
}
class DomNamedNodeMap {
    function getNamedItem($name) {}
    function getNamedItemNS($namespaceURI, $localName) {}
    function item($index) {}
}
class HttpRequestPool {
    function getAttachedRequests() {}
    function send() {}
    function getFinishedRequests() {}
    function detach($request) {}
    function socketSelect() {}
    function reset() {}
    function __construct($request) {}
    function socketPerform() {}
    function __destruct() {}
    function attach($request) {}
}
class HttpInflateStream {
    function flush($data) {}
    function factory($flags = 0, $class_name = 'HttpInflateStream') {}
    function finish($data) {}
    function update($data) {}
    function __construct($flags = 0) {}
}
class HttpDeflateStream {
    function flush($data) {}
    function factory($flags = 0, $class_name = 'HttpDeflateStream') {}
    function finish($data) {}
    function update($data) {}
    function __construct($flags = 0) {}
}
class HttpMessage {
    function send() {}
    function setResponseCode($code) {}
    function factory($raw_message, $class_name = 'HttpMessage') {}
    function setHeaders($headers) {}
    function getBody() {}
    function addHeaders($headers, $append = FALSE) {}
    function setBody($body) {}
    function toMessageTypeObject() {}
    function detach() {}
    function getHeaders() {}
    function reverse() {}
    function setType($type) {}
    function setHttpVersion($version) {}
    function getRequestMethod() {}
    function setResponseStatus($status) {}
    function setRequestMethod($method) {}
    function prepend($message, $top = TRUE) {}
    function setRequestUrl($url) {}
    function getType() {}
    function guessContentType($magic_file, $magic_mode = MAGIC_MIME) {}
    function getResponseStatus() {}
    function fromEnv($message_type, $class_name = 'HttpMessage') {}
    function getParentMessage() {}
    function __construct($message) {}
    function getHttpVersion() {}
    function fromString($raw_message, $class_name = 'HttpMessage') {}
    function toString($include_parent = FALSE) {}
    function getRequestUrl() {}
    function getHeader($header) {}
    function getResponseCode() {}
}
class HttpRequest {
    function getPutData() {}
    function setCookies($cookies) {}
    function send() {}
    function getRawRequestMessage() {}
    function setQueryData($query_data) {}
    function getResponseMessage() {}
    function getHistory() {}
    function getResponseData() {}
    function getResponseHeader($name) {}
    function addRawPostData($raw_post_data) {}
    function clearHistory() {}
    function getResponseBody() {}
    function getOptions() {}
    function getRawPostData() {}
    function setHeaders($headers) {}
    function getMethod() {}
    function setPutData($put_data) {}
    function setOptions($options) {}
    function addHeaders($headers) {}
    function getQueryData() {}
    function getCookies() {}
    function addCookies($cookies) {}
    function enableCookies() {}
    function setRawPostData($raw_post_data) {}
    function getHeaders() {}
    function getPostFiles() {}
    function setPostFields($post_data) {}
    function getSslOptions() {}
    function setPutFile($file) {}
    function getRawResponseMessage() {}
    function setPostFiles($post_files) {}
    function setUrl($url) {}
    function setContentType($content_type) {}
    function resetCookies($session_only = FALSE) {}
    function addPostFields($post_data) {}
    function getResponseStatus() {}
    function getResponseCookies($flags, $allowed_extras) {}
    function addPutData($put_data) {}
    function getPostFields() {}
    function setMethod($request_method) {}
    function getPutFile() {}
    function __construct($url, $request_method = HTTP_METH_GET, $options) {}
    function addQueryData($query_params) {}
    function getResponseInfo($name) {}
    function addPostFile($name, $file, $content_type = 'applicationxoctetstream') {}
    function getRequestMessage() {}
    function setSslOptions($options) {}
    function addSslOptions($options) {}
    function getUrl() {}
    function getContentType() {}
    function getResponseCode() {}
}
class HttpQueryString {
    function xlate($ie, $oe) {}
    function get($key, $type = 0, $defval = NULL, $delete = FALSE) {}
    function mod($params) {}
    function set($params) {}
    function singleton($global = TRUE) {}
    function __construct($global = TRUE, $add) {}
    function toArray() {}
    function toString() {}
}
class HttpResponse {
    function getContentDisposition() {}
    function send($clean_ob = TRUE) {}
    function setHeader($name, $value, $replace = TRUE) {}
    function getCacheControl() {}
    function setCacheControl($control, $max_age = 0, $must_revalidate = TRUE) {}
    function getLastModified() {}
    function setData($data) {}
    function setLastModified($timestamp) {}
    function getETag() {}
    function setCache($cache) {}
    function setContentDisposition($filename, $inline = FALSE) {}
    function setBufferSize($bytes) {}
    function redirect($url, $params, $session = FALSE, $status) {}
    function getBufferSize() {}
    function setFile($file) {}
    function getFile() {}
    function getRequestBodyStream() {}
    function setETag($etag) {}
    function setGzip($gzip) {}
    function getCache() {}
    function setThrottleDelay($seconds) {}
    function setStream($stream) {}
    function setContentType($content_type) {}
    function capture() {}
    function getData() {}
    function guessContentType($magic_file, $magic_mode=MAGIC_MIME) {}
    function getThrottleDelay() {}
    function getRequestBody() {}
    function getStream() {}
    function getGzip() {}
    function getRequestHeaders() {}
    function status($status) {}
    function getHeader($name) {}
    function getContentType() {}
}
class PDOStatement {
    function fetchAll($fetch_style, $column_index, $ctor_args) {}
    function nextRowset() {}
    function fetch($fetch_style, $cursor_orientation, $cursor_offset) {}
    function fetchColumn($column_number) {}
    function errorCode() {}
    function rowCount() {}
    function bindValue($parameter, $value, $data_type) {}
    function bindParam($parameter, $variable, $data_type, $length, $driver_options) {}
    function columnCount() {}
    function errorInfo() {}
    function fetchObject($class_name, $ctor_args) {}
    function getAttribute($attribute) {}
    function bindColumn($column, $param, $type, $maxlen, $driverdata) {}
    function closeCursor() {}
    function setAttribute($attribute, $value) {}
    function execute($input_parameters) {}
    function getColumnMeta($column) {}
    function setFetchMode($mode) {}
}
class SDO_DAS_Setting {
    function getPropertyIndex() {}
    function getPropertyName() {}
    function getValue() {}
    function getListIndex() {}
}
class SDO_DataObject {
    function getTypeNamespaceURI() {}
    function clear() {}
    function getTypeName() {}
    function getContainer() {}
    function createDataObject($identifier) {}
    function getSequence() {}
}
class SDO_DataFactory {
    function create($type_namespace_uri, $type_name) {}
}
class SDO_Model_Type {
    function isAbstractType() {}
    function isInstance($data_object) {}
    function getNamespaceURI() {}
    function isDataType() {}
    function isOpenType() {}
    function getBaseType() {}
    function getProperties() {}
    function getProperty($identifier) {}
    function isSequencedType() {}
    function getName() {}
}
class SDO_Model_ReflectionDataObject {
    function getInstanceProperties() {}
    function getType() {}
    function getContainmentProperty() {}
    function __construct($data_object) {}
    function export($rdo, $return) {}
}
class SDO_Model_Property {
    function isContainment() {}
    function isMany() {}
    function getName() {}
    function getType() {}
    function getDefault() {}
    function getContainingType() {}
}
class SDO_Sequence {
    function insert($value, $sequenceIndex, $propertyIdentifier) {}
    function getProperty($sequence_index) {}
    function move($toIndex, $fromIndex) {}
}
class SDO_DAS_ChangeSummary {
    function isLogging() {}
    function getOldValues($data_object) {}
    function getOldContainer($data_object) {}
    function getChangedDataObjects() {}
    function getChangeType($dataObject) {}
    function beginLogging() {}
    function endLogging() {}
}
class SDO_List {
    function insert($value, $index) {}
}
class SDO_DAS_DataFactory {
    function addPropertyToType($parent_type_namespace_uri, $parent_type_name, $property_name, $type_namespace_uri, $type_name, $options) {}
    function addType($type_namespace_uri, $type_name, $options) {}
    function getDataFactory() {}
}
class SDO_DAS_DataObject {
    function getChangeSummary() {}
}
class SDO_Exception {
    function getCause() {}
}
class Swish {
    function __construct($index_names) {}
}
class HaruDoc {
    function setPageLayout($layout) {}
    function getCurrentPage() {}
    function getPageLayout() {}
    function setInfoDateAttr($type, $year, $month, $day, $hour, $min, $sec, $ind, $off_hour, $off_min) {}
    function useKREncodings() {}
    function loadPNG($filename, $deferred) {}
    function saveToStream() {}
    function getEncoder($encoding) {}
    function setOpenAction($destination) {}
    function useJPEncodings() {}
    function setPermission($permission) {}
    function createOutline($title, $parent_outline, $encoder) {}
    function output() {}
    function getInfoAttr($type) {}
    function setCurrentEncoder($encoding) {}
    function resetError() {}
    function loadType1($afmfile, $pfmfile) {}
    function setPagesConfiguration($page_per_pages) {}
    function useCNTFonts() {}
    function resetStream() {}
    function setInfoAttr($type, $info) {}
    function getFont($fontname, $encoding) {}
    function setPassword($owner_password, $user_password) {}
    function loadTTC($fontfile, $index, $embed) {}
    function useCNSFonts() {}
    function getStreamSize() {}
    function readFromStream($bytes) {}
    function getCurrentEncoder() {}
    function useKRFonts() {}
    function setPageMode($mode) {}
    function useCNSEncodings() {}
    function useCNTEncodings() {}
    function __construct() {}
    function addPageLabel($first_page, $style, $first_num, $prefix) {}
    function loadJPEG($filename) {}
    function save($file) {}
    function loadRaw($filename, $width, $height, $color_space) {}
    function loadTTF($fontfile, $embed) {}
    function setEncryptionMode($mode, $key_len) {}
    function useJPFonts() {}
    function setCompressionMode($mode) {}
    function addPage() {}
    function insertPage($page) {}
    function getPageMode() {}
}
class HaruImage {
    function getBitsPerComponent() {}
    function getWidth() {}
    function getHeight() {}
    function getSize() {}
    function setMaskImage($mask_image) {}
    function setColorMask($rmin, $rmax, $gmin, $gmax, $bmin, $bmax) {}
    function getColorSpace() {}
}
class HaruAnnotation {
    function setIcon($icon) {}
    function setBorderStyle($width, $dash_on, $dash_off) {}
    function setHighlightMode($mode) {}
    function setOpened($opened) {}
}
class HaruFont {
    function measureText($text, $width, $font_size, $char_space, $word_space, $word_wrap) {}
    function getAscent() {}
    function getEncodingName() {}
    function getCapHeight() {}
    function getUnicodeWidth($character) {}
    function getXHeight() {}
    function getDescent() {}
    function getTextWidth($text) {}
    function getFontName() {}
}
class HaruPage {
    function setLineJoin($join) {}
    function getHorizontalScaling() {}
    function closePath() {}
    function fillStroke($close_path) {}
    function getWidth() {}
    function measureText($text, $width, $wordwrap) {}
    function getWordSpace() {}
    function showTextNextLine($text, $word_space, $char_space) {}
    function arc($x, $y, $ray, $ang1, $ang2) {}
    function ellipse($x, $y, $xray, $yray) {}
    function getTextRise() {}
    function getTextMatrix() {}
    function getTransMatrix() {}
    function getMiterLimit() {}
    function eofill() {}
    function concat($a, $b, $c, $d, $x, $y) {}
    function moveTo($x, $y) {}
    function rectangle($x, $y, $width, $height) {}
    function fill() {}
    function setGrayFill($value) {}
    function getCurrentTextPos() {}
    function getCharSpace() {}
    function createTextAnnotation($rectangle, $text, $encoder) {}
    function setTextRenderingMode($mode) {}
    function setTextLeading($text_leading) {}
    function getCurrentFont() {}
    function setSize($size, $direction) {}
    function setCMYKStroke($c, $m, $y, $k) {}
    function getGMode() {}
    function curveTo2($x2, $y2, $x3, $y3) {}
    function getHeight() {}
    function getRGBFill() {}
    function curveTo($x1, $y1, $x2, $y2, $x3, $y3) {}
    function getCMYKFill() {}
    function moveTextPos($x, $y, $set_leading) {}
    function getStrokingColorSpace() {}
    function setHeight($height) {}
    function getFlatness() {}
    function createURLAnnotation($rectangle, $url) {}
    function getGrayStroke() {}
    function setLineCap($cap) {}
    function circle($x, $y, $ray) {}
    function setRotate($angle) {}
    function moveToNextLine() {}
    function setCMYKFill($c, $m, $y, $k) {}
    function setGrayStroke($value) {}
    function setTextMatrix($a, $b, $c, $d, $x, $y) {}
    function setDash($pattern, $phase) {}
    function drawImage($image, $x, $y, $width, $height) {}
    function curveTo3($x1, $y1, $x3, $y3) {}
    function lineTo($x, $y) {}
    function setRGBFill($r, $g, $b) {}
    function createLinkAnnotation($rectangle, $destination) {}
    function setLineWidth($width) {}
    function getLineCap() {}
    function endText() {}
    function getGrayFill() {}
    function setHorizontalScaling($scaling) {}
    function setMiterLimit($limit) {}
    function setWidth($width) {}
    function getTextRenderingMode() {}
    function setRGBStroke($r, $g, $b) {}
    function setCharSpace($char_space) {}
    function createDestination() {}
    function getDash() {}
    function getRGBStroke() {}
    function setFontAndSize($font, $size) {}
    function getLineJoin() {}
    function textOut($x, $y, $text) {}
    function beginText() {}
    function setSlideShow($type, $disp_time, $trans_time) {}
    function stroke($close_path) {}
    function endPath() {}
    function textRect($left, $top, $right, $bottom, $text, $align) {}
    function getTextLeading() {}
    function showText($text) {}
    function getLineWidth() {}
    function setFlatness($flatness) {}
    function getFillingColorSpace() {}
    function eoFillStroke($close_path) {}
    function setTextRise($rise) {}
    function getCMYKStroke() {}
    function getCurrentFontSize() {}
    function getTextWidth($text) {}
    function setWordSpace($word_space) {}
    function getCurrentPos() {}
}
class HaruEncoder {
    function getUnicode($character) {}
    function getWritingMode() {}
    function getType() {}
    function getByteType($text, $index) {}
}
class HaruDestination {
    function setXYZ($left, $top, $zoom) {}
    function setFitV($left) {}
    function setFitBH($top) {}
    function setFitR($left, $bottom, $right, $top) {}
    function setFit() {}
    function setFitBV($left) {}
    function setFitB() {}
    function setFitH($top) {}
}
class HaruOutline {
    function setDestination($destination) {}
    function setOpened($opened) {}
}
class ImagickPixelIterator {
    function syncIterator() {}
    function setIteratorFirstRow() {}
    function getCurrentIteratorRow() {}
    function clear() {}
    function getPreviousIteratorRow() {}
    function destroy() {}
    function setIteratorLastRow() {}
    function newPixelRegionIterator($wand, $x, $y, $columns, $rows) {}
    function newPixelIterator($wand) {}
    function resetIterator() {}
    function getIteratorRow() {}
    function __construct($wand) {}
    function setIteratorRow($row) {}
    function getNextIteratorRow() {}
}
class ImagickPixel {
    function getColorValue($color) {}
    function setColorValue($color, $value) {}
    function getColorCount() {}
    function clear() {}
    function destroy() {}
    function getColor($normalized) {}
    function setColor($color) {}
    function getColorAsString() {}
    function setHSL($hue, $saturation, $luminosity) {}
    function getHSL() {}
    function __construct($color) {}
    function isSimilar($color, $fuzz) {}
}
class Imagick {
    function getImageTotalInkDensity() {}
    function getImageCompose() {}
    function spliceImage($width, $height, $x, $y) {}
    function setType($image_type) {}
    function shearImage($background, $x_shear, $y_shear) {}
    function displayImage($servername) {}
    function getImageBluePrimary($x, $y) {}
    function gammaImage($gamma, $channel) {}
    function setResolution($x_resolution, $y_resolution) {}
    function setImageType($image_type) {}
    function getImageFormat() {}
    function sharpenImage($radius, $sigma, $channel) {}
    function setImageColormapColor($index, $color) {}
    function getImagePixelColor($x, $y) {}
    function compareImageChannels($image, $channelType, $metricType) {}
    function adaptiveThresholdImage($width, $height, $offset) {}
    function getImageInterpolateMethod() {}
    function previewImages($preview) {}
    function setImageMatte($matte) {}
    function colorizeImage($colorize, $opacity) {}
    function getPixelRegionIterator($x, $y, $columns, $rows) {}
    function getImageChannelDepth($channelType) {}
    function setFirstIterator() {}
    function setImageOrientation($orientation) {}
    function quantizeImage($numberColors, $colorspace, $treedepth, $dither, $measureError) {}
    function getSizeOffset() {}
    function shadowImage($opacity, $sigma, $x, $y) {}
    function quantizeImages($numberColors, $colorspace, $treedepth, $dither, $measureError) {}
    function gaussianBlurImage($radius, $sigma, $channel) {}
    function getImageRedPrimary() {}
    function getImageBorderColor() {}
    function setImageMatteColor($matte) {}
    function getImageHeight() {}
    function getImageProperty($name) {}
    function trimImage($fuzz) {}
    function oilPaintImage($radius) {}
    function getImageGeometry() {}
    function getImageChannelDistortion($reference, $channel, $metric) {}
    function averageImages() {}
    function setImageExtent($columns, $rows) {}
    function getImageLength() {}
    function getImageVirtualPixelMethod() {}
    function randomThresholdImage($low, $high, $channel) {}
    function getHomeURL() {}
    function getImageChannelExtrema($channel) {}
    function frameImage($matte_color, $width, $height, $inner_bevel, $outer_bevel) {}
    function combineImages($channelType) {}
    function getImageChannelStatistics() {}
    function getImageWidth() {}
    function setFilename($filename) {}
    function swirlImage($degrees) {}
    function minifyImage() {}
    function getImageRegion($width, $height, $x, $y) {}
    function getImageUnits() {}
    function setPage($width, $height, $x, $y) {}
    function getImageDepth() {}
    function setResourceLimit($type, $limit) {}
    function clutImage($lookup_table, $channel) {}
    function setImageProfile($name, $profile) {}
    function cropThumbnailImage($width, $height) {}
    function reduceNoiseImage($radius) {}
    function removeImage() {}
    function getImageBlob() {}
    function flipImage() {}
    function getImageSize() {}
    function getImageMatte() {}
    function getNumberImages() {}
    function getQuantumDepth() {}
    function despeckleImage() {}
    function clear() {}
    function setImageDispose($dispose) {}
    function stripImage() {}
    function setSize($columns, $rows) {}
    function polaroidImage($properties, $angle) {}
    function addImage($source) {}
    function readImage($filename) {}
    function getImageRenderingIntent() {}
    function nextImage() {}
    function uniqueImageColors() {}
    function medianFilterImage($radius) {}
    function resizeImage($columns, $rows, $filter, $blur, $fit) {}
    function getCompressionQuality() {}
    function adaptiveResizeImage($columns, $rows, $fit) {}
    function sampleImage($columns, $rows) {}
    function setImageGamma($gamma) {}
    function destroy() {}
    function setImageFilename($filename) {}
    function setImageColorspace($colorspace) {}
    function cycleColormapImage($displace) {}
    function sepiaToneImage($threshold) {}
    function mosaicImages() {}
    function getImagePage() {}
    function setImageGreenPrimary($x, $y) {}
    function getCopyright() {}
    function setImageProperty($name, $value) {}
    function blackThresholdImage($threshold) {}
    function setImageBackgroundColor($background) {}
    function setLastIterator() {}
    function identifyImage($appendRawOutput) {}
    function steganoImage($watermark_wand, $offset) {}
    function valid() {}
    function getImageDistortion($reference, $metric) {}
    function normalizeImage($channel) {}
    function getImageGamma() {}
    function getImageProfile($name) {}
    function vignetteImage($blackPoint, $whitePoint, $x, $y) {}
    function getImageMagickLicense() {}
    function chopImage($width, $height, $x, $y) {}
    function getQuantumRange() {}
    function colorFloodfillImage($fill, $fuzz, $bordercolor, $x, $y) {}
    function getPixelIterator() {}
    function charcoalImage($radius, $sigma) {}
    function readImageFile($filehandle, $fileName) {}
    function setImageChannelDepth($channel, $depth) {}
    function deconstructImages() {}
    function tintImage($tint, $opacity) {}
    function setBackgroundColor($background) {}
    function evaluateImage($op, $constant, $channel) {}
    function implodeImage($radius) {}
    function setSamplingFactors($factors) {}
    function getImageHistogram() {}
    function setIteratorIndex($index) {}
    function rotateImage($background, $degrees) {}
    function transverseImage() {}
    function cropImage($width, $height, $x, $y) {}
    function setImageTicksPerSecond($ticks_persecond) {}
    function stereoImage($offset_wand) {}
    function montageImage($draw, $tile_geometry, $thumbnail_geometry, $mode, $frame) {}
    function sketchImage($radius, $sigma, $angle) {}
    function fxImage($expression, $channel) {}
    function setImage($replace) {}
    function thumbnailImage($columns, $rows, $fit) {}
    function getImageColorspace() {}
    function render() {}
    function setImageIterations($iterations) {}
    function radialBlurImage($angle, $channel) {}
    function blurImage($radius, $sigma, $channel) {}
    function getImageIterations() {}
    function getImageChannelMean($channel) {}
    function setImageRenderingIntent($rendering_intent) {}
    function labelImage($label) {}
    function getImageResolution() {}
    function setCompressionQuality($quality) {}
    function appendImages($stack) {}
    function adaptiveBlurImage($radius, $sigma, $channel) {}
    function setImageScene($scene) {}
    function setImageWhitePoint($x, $y) {}
    function paintFloodfillImage($fill, $fuzz, $bordercolor, $x, $y) {}
    function getImageColormapColor($index) {}
    function getInterlaceScheme() {}
    function drawImage($draw) {}
    function getImageOrientation() {}
    function addNoiseImage($noise_type, $channel) {}
    function getImage() {}
    function setImageInterpolateMethod($method) {}
    function setImageDelay($delay) {}
    function newImage($cols, $rows, $background, $format) {}
    function writeImage($filename) {}
    function separateImageChannel($channel) {}
    function flattenImages() {}
    function queryFonts($pattern) {}
    function setCompression($compression) {}
    function sigmoidalContrastImage($sharpen, $alpha, $beta, $channel) {}
    function transformImage($crop, $geometry) {}
    function getImageIndex() {}
    function getFilename() {}
    function morphImages($number_frames) {}
    function getOption($key) {}
    function getImageDelay() {}
    function posterizeImage($levels, $dither) {}
    function profileImage($name, $profile) {}
    function getImageDispose() {}
    function getFormat() {}
    function setOption($key, $value) {}
    function getImageProfiles($pattern, $only_names) {}
    function magnifyImage() {}
    function getSize() {}
    function compareImageLayers($method) {}
    function pingImage($filename) {}
    function getSamplingFactors() {}
    function shadeImage($gray, $azimuth, $elevation) {}
    function coalesceImages() {}
    function setImageInterlaceScheme($interlace_scheme) {}
    function motionBlurImage($radius, $sigma, $angle) {}
    function getVersion() {}
    function shaveImage($columns, $rows) {}
    function setImageVirtualPixelMethod($method) {}
    function getImageType() {}
    function whiteThresholdImage($threshold) {}
    function pingImageBlob($image) {}
    function setImageBorderColor($border) {}
    function hasPreviousImage() {}
    function setImageUnits($units) {}
    function setInterlaceScheme($interlace_scheme) {}
    function unsharpMaskImage($radius, $sigma, $amount, $threshold, $channel) {}
    function levelImage($blackPoint, $gamma, $whitePoint, $channel) {}
    function setImageResolution($x_resolution, $y_resolution) {}
    function flopImage() {}
    function raiseImage($width, $height, $x, $y, $raise) {}
    function linearStretchImage($blackPoint, $whitePoint) {}
    function solarizeImage($threshold) {}
    function getImageColors() {}
    function textureImage($texture_wand) {}
    function getImageGreenPrimary() {}
    function setImageRedPrimary($x, $y) {}
    function scaleImage($cols, $rows, $fit) {}
    function setImageDepth($depth) {}
    function modulateImage($brightness, $saturation, $hue) {}
    function setImageFormat($format) {}
    function getImageTicksPerSecond() {}
    function getPage() {}
    function convolveImage($kernel, $channel) {}
    function distortImage($method, $arguments, $bestfit) {}
    function optimizeImageLayers() {}
    function getImageMatteColor() {}
    function getReleaseDate() {}
    function getResourceLimit($type) {}
    function getImageFilename() {}
    function setImageCompression($compression) {}
    function __construct($files) {}
    function getImageInterlaceScheme() {}
    function pingImageFile($filehandle, $fileName) {}
    function rollImage($x, $y) {}
    function resampleImage($x_resolution, $y_resolution, $filter, $blur) {}
    function getImageProperties($pattern, $only_names) {}
    function displayImages($servername) {}
    function clipPathImage($pathname, $inside) {}
    function affineTransformImage($matrix) {}
    function queryFormats($pattern) {}
    function getImageWhitePoint() {}
    function removeImageProfile($name) {}
    function previousImage() {}
    function commentImage($comment) {}
    function setImageBluePrimary($x, $y) {}
    function enhanceImage() {}
    function newPseudoImage($columns, $rows, $pseudoString) {}
    function annotateImage($draw_settings, $x, $y, $angle, $text) {}
    function getPackageName() {}
    function roundCorners($x_rounding, $y_rounding, $stroke_width, $displace, $size_correction) {}
    function setImageBias($bias) {}
    function setImageOpacity($opacity) {}
    function getImageScene() {}
    function getImageBackgroundColor() {}
    function mapImage($map, $dither) {}
    function getImageExtrema() {}
    function edgeImage($radius) {}
    function setImageIndex($index) {}
    function getIteratorIndex() {}
    function getCompression() {}
    function adaptiveSharpenImage($radius, $sigma, $channel) {}
    function hasNextImage() {}
    function waveImage($amplitude, $length) {}
    function setImageCompose($compose) {}
    function readImageBlob($image, $filename) {}
    function paintOpaqueImage($target, $fill, $fuzz, $channel) {}
    function setImagePage($width, $height, $x, $y) {}
    function equalizeImage() {}
    function contrastImage($sharpen) {}
    function negateImage($gray, $channel) {}
    function writeImages($filename, $adjoin) {}
    function clipImage() {}
    function setFormat($format) {}
    function contrastStretchImage($black_point, $white_point, $channel) {}
    function borderImage($bordercolor, $width, $height) {}
    function setSizeOffset($columns, $rows, $offset) {}
    function paintTransparentImage($target, $alpha, $fuzz) {}
    function thresholdImage($threshold, $channel) {}
    function matteFloodfillImage($alpha, $fuzz, $bordercolor, $x, $y) {}
    function embossImage($radius, $sigma) {}
    function queryFontMetrics($properties, $text, $multiline) {}
    function getImageSignature() {}
    function compareImages($compare, $metric) {}
    function getResource($type) {}
    function current() {}
    function compositeImage($composite_object, $composite, $x, $y, $channel) {}
    function spreadImage($radius) {}
}
class ImagickDraw {
    function getStrokeAntialias() {}
    function setFontStretch($fontStretch) {}
    function push() {}
    function setViewbox($x1, $y1, $x2, $y2) {}
    function polygon($coordinates) {}
    function pushDefs() {}
    function pathCurveToQuadraticBezierAbsolute($x1, $y1, $x, $y) {}
    function getFillOpacity() {}
    function pathCurveToAbsolute($x1, $y1, $x2, $y2, $x, $y) {}
    function line($sx, $sy, $ex, $ey) {}
    function pathLineToRelative($x, $y) {}
    function roundRectangle($x1, $y1, $x2, $y2, $rx, $ry) {}
    function arc($sx, $sy, $ex, $ey, $sd, $ed) {}
    function pathLineToVerticalRelative($y) {}
    function ellipse($ox, $oy, $rx, $ry, $start, $end) {}
    function getTextEncoding() {}
    function pathEllipticArcAbsolute($rx, $ry, $x_axis_rotation, $large_arc_flag, $sweep_flag, $x, $y) {}
    function pop() {}
    function getClipUnits() {}
    function pathLineToHorizontalRelative($x) {}
    function rectangle($x1, $y1, $x2, $y2) {}
    function pathClose() {}
    function setStrokePatternURL($stroke_url) {}
    function point($x, $y) {}
    function skewY($degrees) {}
    function annotation($x, $y, $text) {}
    function bezier($coordinates) {}
    function pathMoveToAbsolute($x, $y) {}
    function composite($compose, $x, $y, $width, $height, $compositeWand) {}
    function clear() {}
    function comment($comment) {}
    function pathStart() {}
    function setClipUnits($clip_units) {}
    function pathEllipticArcRelative($rx, $ry, $x_axis_rotation, $large_arc_flag, $sweep_flag, $x, $y) {}
    function pathLineToVerticalAbsolute($y) {}
    function setFillColor($fill_pixel) {}
    function popPattern() {}
    function getStrokeLineJoin() {}
    function matte($x, $y, $paintMethod) {}
    function popDefs() {}
    function rotate($degrees) {}
    function destroy() {}
    function getGravity() {}
    function pathLineToAbsolute($x, $y) {}
    function getVectorGraphics() {}
    function setFillPatternURL($fill_url) {}
    function getTextUnderColor() {}
    function skewX($degrees) {}
    function pathLineToHorizontalAbsolute($x) {}
    function setClipPath($clip_mask) {}
    function circle($ox, $oy, $px, $py) {}
    function setStrokeAntialias($stroke_antialias) {}
    function render() {}
    function getFontFamily() {}
    function setStrokeColor($stroke_pixel) {}
    function setFontStyle($style) {}
    function getClipRule() {}
    function getFillColor() {}
    function popClipPath() {}
    function getFont() {}
    function setStrokeWidth($stroke_width) {}
    function getFillRule() {}
    function getTextAlignment() {}
    function pathCurveToRelative($x1, $y1, $x2, $y2, $x, $y) {}
    function getTextAntialias() {}
    function getTextDecoration() {}
    function pathCurveToSmoothAbsolute($x2, $y2, $x, $y) {}
    function setFillAlpha($opacity) {}
    function setStrokeMiterLimit($miterlimit) {}
    function setFillRule($fill_rule) {}
    function getFontSize() {}
    function pathCurveToSmoothRelative($x2, $y2, $x, $y) {}
    function setTextEncoding($encoding) {}
    function pushPattern($pattern_id, $x, $y, $width, $height) {}
    function getStrokeColor($stroke_color) {}
    function setGravity($gravity) {}
    function setFillOpacity($fillOpacity) {}
    function setStrokeLineJoin($linejoin) {}
    function getStrokeOpacity() {}
    function getStrokeMiterLimit() {}
    function scale($x, $y) {}
    function setStrokeOpacity($stroke_opacity) {}
    function getStrokeLineCap() {}
    function setFontFamily($font_family) {}
    function setTextAntialias($antiAlias) {}
    function polyline($coordinates) {}
    function affine($affine) {}
    function setStrokeDashArray($dashArray) {}
    function pathMoveToRelative($x, $y) {}
    function translate($x, $y) {}
    function setStrokeAlpha($opacity) {}
    function getFontWeight() {}
    function __construct() {}
    function setFont($font_name) {}
    function setTextUnderColor($under_color) {}
    function pathCurveToQuadraticBezierSmoothAbsolute($x, $y) {}
    function getStrokeWidth() {}
    function setTextAlignment($alignment) {}
    function setVectorGraphics($xml) {}
    function setStrokeLineCap($linecap) {}
    function setClipRule($fill_rule) {}
    function pathFinish() {}
    function setStrokeDashOffset($dash_offset) {}
    function pathCurveToQuadraticBezierSmoothRelative($x, $y) {}
    function getStrokeDashArray() {}
    function setFontWeight($font_weight) {}
    function pushClipPath($clip_mask_id) {}
    function getFontStyle() {}
    function getClipPath() {}
    function setFontSize($pointsize) {}
    function setTextDecoration($decoration) {}
    function color($x, $y, $paintMethod) {}
    function getStrokeDashOffset() {}
    function pathCurveToQuadraticBezierRelative($x1, $y1, $x, $y) {}
}
class mysqli_result {
    function fetch_array($resulttype) {}
    function fetch_row() {}
    function field_seek($fieldnr) {}
    function fetch_object($class_name, $params) {}
    function free() {}
    function data_seek($offset) {}
    function fetch_field() {}
    function fetch_field_direct($fieldnr) {}
    function fetch_assoc() {}
    function fetch_fields() {}
}
class mysqli {
    function options($option, $value) {}
    function rollback() {}
    function set_charset($charset) {}
    function get_warnings() {}
    function escape_string($escapestr) {}
    function select_db($dbname) {}
    function stat() {}
    function dump_debug_info() {}
    function ssl_set($key, $cert, $ca, $capath, $cipher) {}
    function real_connect($host, $username, $passwd, $dbname, $port, $socket, $flags) {}
    function query($query, $resultmode) {}
    function next_result() {}
    function character_set_name() {}
    function debug($message) {}
    function kill($processid) {}
    function get_client_version() {}
    function autocommit($mode) {}
    function get_charset() {}
    function change_user($user, $password, $database) {}
    function ping() {}
    function get_client_info() {}
    function more_results() {}
    function commit() {}
    function multi_query($query) {}
    function close() {}
}
class mysqli_stmt {
    function bind_param($types, $var1) {}
    function send_long_data($param_nr, $data) {}
    function fetch() {}
    function get_warnings($stmt) {}
    function result_metadata() {}
    function prepare($query) {}
    function free_result() {}
    function data_seek($offset) {}
    function reset() {}
    function execute() {}
    function store_result() {}
    function bind_result($var1) {}
    function close() {}
}
class mysqli_driver {
    function embedded_server_start($start, $arguments, $groups) {}
    function embedded_server_end() {}
}
class SplStack {
    function setIteratorMode($mode) {}
}
class SplHeap {
    function next() {}
    function valid() {}
    function recoverFromCorruption() {}
    function key() {}
    function isEmpty() {}
    function rewind() {}
    function extract() {}
    function compare($value1, $value2) {}
    function top() {}
    function current() {}
    function count() {}
    function insert($value) {}
}
class FilterIterator {
    function next() {}
    function getInnerIterator() {}
    function valid() {}
    function key() {}
    function rewind() {}
    function current() {}
}
class SplDoublyLinkedList {
    function push($value) {}
    function pop() {}
    function next() {}
    function unshift($value) {}
    function shift() {}
    function valid() {}
    function getIteratorMode() {}
    function key() {}
    function offsetSet($index, $newval) {}
    function isEmpty() {}
    function rewind() {}
    function bottom() {}
    function offsetGet($index) {}
    function top() {}
    function offsetUnset($index) {}
    function setIteratorMode($mode) {}
    function offsetExists($index) {}
    function current() {}
    function count() {}
}
class RecursiveIteratorIterator {
    function next() {}
    function valid() {}
    function key() {}
    function getSubIterator() {}
    function rewind() {}
    function getDepth() {}
    function current() {}
}
class DirectoryIterator {
    function isFile() {}
    function isLink() {}
    function isExecutable() {}
    function getATime() {}
    function getInode() {}
    function isDir() {}
    function getPerms() {}
    function next() {}
    function isDot() {}
    function getGroup() {}
    function getPath() {}
    function valid() {}
    function key() {}
    function getType() {}
    function rewind() {}
    function isWritable() {}
    function getOwner() {}
    function getFilename() {}
    function getPathname() {}
    function getSize() {}
    function getMTime() {}
    function getCTime() {}
    function isReadable() {}
    function current() {}
}
class CachingIterator {
    function next() {}
    function __toString() {}
    function valid() {}
    function rewind() {}
    function hasNext() {}
}
class SplMinHeap {
    function compare($value1, $value2) {}
}
class ArrayIterator {
    function next() {}
    function valid() {}
    function key() {}
    function rewind() {}
    function seek($position) {}
    function current() {}
}
class SplPriorityQueue {
    function next() {}
    function valid() {}
    function recoverFromCorruption() {}
    function key() {}
    function isEmpty() {}
    function rewind() {}
    function setExtractFlags($flags) {}
    function extract() {}
    function compare($priority1, $priority1) {}
    function top() {}
    function current() {}
    function count() {}
    function insert($value, $priority) {}
}
class RecursiveCachingIterator {
    function getChildren() {}
    function hasChildren() {}
}
class RecursiveDirectoryIterator {
    function next() {}
    function key() {}
    function getChildren() {}
    function rewind() {}
    function hasChildren($allow_links) {}
}
class ArrayObject {
    function offsetSet($index, $newval) {}
    function offsetGet($index) {}
    function append($newval) {}
    function offsetUnset($index) {}
    function offsetExists($index) {}
    function getIterator() {}
    function count() {}
}
class SplMaxHeap {
    function compare($value1, $value2) {}
}
class SimpleXMLIterator {
    function next() {}
    function valid() {}
    function key() {}
    function getChildren() {}
    function rewind() {}
    function hasChildren() {}
    function current() {}
}
class ParentIterator {
    function next() {}
    function getChildren() {}
    function rewind() {}
    function hasChildren() {}
}
class SplQueue {
    function enqueue($value) {}
    function dequeue() {}
    function setIteratorMode($mode) {}
}
class LimitIterator {
    function next() {}
    function valid() {}
    function rewind() {}
    function seek($position) {}
    function getPosition() {}
}
class tidyNode {
    function isPhp() {}
    function isComment() {}
    function isAsp() {}
    function isHtml() {}
    function hasChildren() {}
    function isJste() {}
    function getParent() {}
    function isText() {}
    function hasSiblings() {}
}
class tidy_node {
    function next() {}
    function get_attr($attrib_id) {}
    function prev() {}
    function get_nodes($node_id) {}
}
class tidy {
    function __construct($filename, $config, $encoding, $use_include_path) {}
}
class ZipArchive {
    function getFromName($name, $flags) {}
    function unchangeName($name) {}
    function getCommentIndex($index, $flags) {}
    function statName($name, $flags) {}
    function getFromIndex($index, $flags) {}
    function unchangeIndex($index) {}
    function statIndex($index, $flags) {}
    function getStream($name) {}
    function getArchiveComment() {}
    function addEmptyDir($dirname) {}
    function close() {}
    function setCommentIndex($index, $comment) {}
    function deleteName($name) {}
    function renameIndex($index, $newname) {}
    function addFile($filename, $localname) {}
    function open($filename, $flags) {}
    function deleteIndex($index) {}
    function getNameIndex($index) {}
    function extractTo($destination, $entries) {}
    function locateName($name, $flags) {}
    function addFromString($localname, $contents) {}
    function renameName($name, $newname) {}
    function setCommentName($name, $comment) {}
    function unchangeArchive() {}
    function getCommentName($name, $flags) {}
    function setArchiveComment($comment) {}
    function unchangeAll() {}
}
class SDO_DAS_XML {
    function saveFile($xdoc, $xml_file, $indent) {}
    function saveString($xdoc, $indent) {}
    function addTypes($xsd_file) {}
    function createDocument($document_element_name) {}
    function create($xsd_file, $key) {}
    function createDataObject($namespace_uri, $type_name) {}
    function loadFile($xml_file) {}
    function loadString($xml_string) {}
}
class SDO_DAS_XML_Document {
    function getRootElementURI() {}
    function getRootElementName() {}
    function setEncoding($encoding) {}
    function setXMLDeclaration($xmlDeclatation) {}
    function getRootDataObject() {}
    function setXMLVersion($xmlVersion) {}
}
class SDO_DAS_Relational {
    function executePreparedQuery($database_handle, $prepared_statement, $value_list, $column_specifier) {}
    function executeQuery($database_handle, $SQL_statement, $column_specifier) {}
    function createRootDataObject() {}
    function applyChanges($database_handle, $root_data_object) {}
    function __construct($database_metadata, $application_root_type, $SDO_containment_references_metadata) {}
}
class MessageFormatter {
    function getPattern() {}
    function parse($value) {}
    function create($locale, $pattern) {}
    function formatMessage($locale, $pattern, $args) {}
    function getErrorCode() {}
    function getLocale() {}
    function setPattern($pattern) {}
    function format($args) {}
    function getErrorMessage() {}
    function parseMessage($locale, $value) {}
}
class Normalizer {
    function normalize($input, $form) {}
    function isNormalized($input, $form) {}
}
class IntlDateFormatter {
    function getCalendar() {}
    function getPattern() {}
    function parse($value, $position) {}
    function create($locale, $datetype, $timetype, $timezone, $calendar, $pattern) {}
    function getTimeZoneId() {}
    function localtime($value, $position) {}
    function isLenient() {}
    function getErrorCode() {}
    function getLocale($which) {}
    function setPattern($pattern) {}
    function setLenient($lenient) {}
    function getTimeType() {}
    function getDateType() {}
    function format($value) {}
    function setCalendar($which) {}
    function setTimeZoneId($zone) {}
    function getErrorMessage() {}
}
class NumberFormatter {
    function formatCurrency($value, $currency) {}
    function parseCurrency($value, $currency, $position) {}
    function getPattern() {}
    function parse($value, $type, $position) {}
    function create($locale, $style, $pattern) {}
    function getErrorCode() {}
    function getLocale($type) {}
    function setPattern($pattern) {}
    function getAttribute($attr) {}
    function format($value, $type) {}
    function getSymbol($attr) {}
    function setSymbol($attr, $value) {}
    function getTextAttribute($attr) {}
    function setTextAttribute($attr, $value) {}
    function setAttribute($attr, $value) {}
    function getErrorMessage() {}
}
class Collator {
    function create($locale) {}
    function setStrength($strength) {}
    function getErrorCode() {}
    function getLocale($type) {}
    function sortWithSortKeys($arr) {}
    function getAttribute($attr) {}
    function compare($str1, $str2) {}
    function asort($arr, $sort_flag) {}
    function getStrength() {}
    function setAttribute($attr, $val) {}
    function sort($arr, $sort_flag) {}
    function getErrorMessage() {}
}
class Locale {
    function parseLocale($locale) {}
    function getRegion($locale) {}
    function getDisplayName($locale, $in_locale) {}
    function getDisplayScript($locale, $in_locale) {}
    function getPrimaryLanguage($locale) {}
    function getAllVariants($locale) {}
    function composeLocale($subtags) {}
    function filterMatches($langtag, $locale) {}
    function getDefault() {}
    function getKeywords($locale) {}
    function getDisplayRegion($locale, $in_locale) {}
    function lookup($langtag, $locale, $default) {}
    function acceptFromHttp($header) {}
    function getDisplayLanguage($locale, $in_locale) {}
    function getDisplayVariant($locale, $in_locale) {}
    function getScript($locale) {}
    function setDefault($locale) {}
}
class SQLite3_stmt {
    function clear() {}
    function bindValue($param_number, $param, $type) {}
    function bindParam($param_number, $param, $type) {}
    function reset() {}
    function paramCount() {}
    function execute() {}
    function close() {}
}
class SQLite3_result {
    function numColumns() {}
    function columnName($column_number) {}
    function finalize() {}
    function columnType($column_number) {}
    function reset() {}
    function fetchArray($mode) {}
}
class SQLite3 {
    function loadExtension($shared_library) {}
    function version() {}
    function exec($query) {}
    function createFunction($name, $callback, $argument_count) {}
    function lastErrorMsg() {}
    function lastErrorCode() {}
    function querySingle($query, $entire_row) {}
    function query($query) {}
    function prepare($query) {}
    function open($filename, $flags, $encryption_key) {}
    function createAggregate($name, $step_callback, $final_callback, $argument_count) {}
    function lastInsertRowID() {}
    function __construct($filename, $flags, $encryption_key) {}
    function changes() {}
    function escapeString($value) {}
    function close() {}
}
