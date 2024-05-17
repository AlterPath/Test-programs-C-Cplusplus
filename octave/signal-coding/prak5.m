clear; clc; close all;
pkg load communications;
text = 'либо дождик, либо снег, либо любит, либо нет';

unique_chars = unique(text);
frequencies = zeros(size(unique_chars));
for i = 1:length(unique_chars)
  frequencies(i) = sum(text == unique_chars(i));
end

nodes = struct('char', unique_chars, 'freq', num2cell(frequencies), 'left', [], 'right', []);

while length(nodes) > 1
  [~, sorted_indices] = sort([nodes.freq]);
  two_smallest = sorted_indices(1:2);
  new_node.char = '';
  new_node.freq = nodes(two_smallest(1)).freq + nodes(two_smallest(2)).freq;
  new_node.left = nodes(two_smallest(1));
  new_node.right = nodes(two_smallest(2));
  nodes(two_smallest) = [];
  nodes = [nodes, new_node];
end

for i = 1:length(frequencies)
  fr(i) = frequencies(i)/length(text);
end

huffman_tree = nodes;
hd = huffmandict(unique_chars, fr);
huffman_codes = huffmanenco(text, hd);

disp('Частоты появления символов:');
for i = 1:length(unique_chars)
  disp([unique_chars(i) ': ' num2str(frequencies(i))]);
end

disp('Коды Хаффмана:');
for i = 1:length(unique_chars)
  if unique_chars(i) == ' '
      disp(['пробел: ' huffman_codes.(' ')]);
  else
      disp([unique_chars(i) ': ' huffman_codes.(unique_chars(i))]);
  end
end

total_length = 0;
for i = 1:length(unique_chars)
  total_length = total_length + length(huffman_codes.(unique_chars(i))) * frequencies(i);
end
average_length = total_length / sum(frequencies);
disp(['Средняя длина кодового слова: ' num2str(average_length) ' бит']);

total_bits = total_length;
disp(['Затраты на передачу текста: ' num2str(total_bits) ' бит']);

