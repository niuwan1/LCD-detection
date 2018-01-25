for i in range(pred_image.shape[0]):
	for j in range(pred_image.shape[1]):
		if pred_image[i][j] == 0:
			img[i][j][0] = 255
			img[i][j][1] = 0
			img[i][j][2] = 0
		elif pred_image[i][j] == 1:
			img[i][j][0] = 0
			img[i][j][1] = 0
			img[i][j][2] = 255
		elif pred_image[i][j] == 2:
			img[i][j][0] = 255
			img[i][j][1] = 255
			img[i][j][2] = 255
		else:
			img[i][j][0] = 0
			img[i][j][1] = 0
			img[i][j][2] = 0
for i in range(h):
	for j in range(w):
		snow_data.append(all_channel_2[i * 28:(i + 1) * 28,j * 28:(j + 1) * 28])
